#include <iostream>
#include <iomanip>
#include <fstream>
#include <pthread.h>
#include <map>
#include <vector>
#include <string>
#include <semaphore.h>
#include <cstring>

using namespace std;

// Structure for inventory items
struct InventoryItem {
    unsigned int productID;
    double price;
    unsigned int stock;
    string description;
};


// Structure for orders
struct Order {
    unsigned int customerID;
    unsigned int productID;
    unsigned int quantity;
    bool isEndMarker;  // Flag to indicate end of production
    int producerID;    // To track which producer created this order
};


// Global variables
map<unsigned int, InventoryItem> inventory;  // Stores inventory data
const int MAX_BUFFER_SIZE = 30;             // Maximum buffer size
const int MAX_PRODUCERS = 9;                // Maximum number of producers

// Bounded buffer variables
Order* buffer;                              // Circular buffer for orders
int bufferSize;                             // Actual buffer size (from args)
int in = 0;                                 // Producer inserts at this index
int out = 0;                                // Consumer removes from this index
int count = 0;                              // Number of items in buffer
int numProducers;                           // Number of producer threads

// Semaphores for synchronization
sem_t emptySlots;                           // Counts empty buffer slots
sem_t full;                                 // Counts filled buffer slots
sem_t mutex;                                // Controls access to buffer

// Global variables for error handling
pthread_mutex_t errorMutex = PTHREAD_MUTEX_INITIALIZER;
bool hasError = false;
string errorMessage;

// Function to safely report errors
void reportError(const string& message) {
    pthread_mutex_lock(&errorMutex);
    hasError = true;
    errorMessage = message;
    pthread_mutex_unlock(&errorMutex);
}

// Function to open inventory.old, extract values, store the values in inventory map
void LoadInventory() {
    ifstream file("inventory.old");

    if (!file) {
        cerr << "Error: Could not open inventory file." << endl;
        return;
    }

    unsigned int id;
    double price;
    unsigned int stock;
    string desc;

    while (file >> id >> price >> stock) {
        getline(file >> ws, desc);
        inventory[id] = {id, price, stock, desc};
    }

    file.close();
}

// Save the updates to inventory.new
void SaveInventory() {
    ofstream file("inventory.new");
    
    if(!file) {
        cerr << "Error: Could not create new inventory file." << endl;
        return;
    }

    for (const auto& item : inventory) {
        file << right << setw(6) << item.second.productID << " " 
             << right << setw(5) << fixed << setprecision(2) << item.second.price << " " 
             << right << setw(5) << item.second.stock << " " 
             << item.second.description << endl;
    }

    file.close();
}

// Save transactions into file "log"
void LogTransaction(unsigned int customerID, unsigned int productID, string productDescription, 
    unsigned int quantity, double transactionAmount, bool result) {
ofstream logFile("log", ios::app);

if (!logFile) {
cerr << "Error: Could not create log file." << endl;
return;
}

logFile << right << setfill('0') << setw(7) << customerID << " "
<< setw(6) << productID << " "
<< left << setfill(' ') << setw(30) << productDescription << " "
<< right << setw(5) << quantity << "  "
<< left << "$" << setw(9) << fixed << setprecision(2) << transactionAmount << " "
<< (result ? "filled" : "rejected") << endl;

logFile.close();
}

// The producer thread function
void* ProducerFunction(void* arg) {
    int producerID = *((int*)arg);
    string filename = "orders" + to_string(producerID);
    
    ifstream file(filename);
    if (!file) {
        string msg = "Error: Producer " + to_string(producerID) + " could not open " + filename + ".";
        reportError(msg);
        
        // Still need to insert end marker even on error
        // This ensures the consumer doesn't deadlock
        sem_wait(&emptySlots);
        sem_wait(&mutex);
        
        buffer[in] = {0, 0, 0, true, producerID}; // End marker
        in = (in + 1) % bufferSize;
        count++;
        
        sem_post(&mutex);
        sem_post(&full);
        
        pthread_exit((void*)1); // Return error status
    }

    // Extract order attributes
    unsigned int customerID, productID, quantity;
    while (file >> customerID >> productID >> quantity) {
        // Create an order
        Order order = {customerID, productID, quantity, false, producerID};
        
        // Add the order to the buffer
        sem_wait(&emptySlots);   // Wait for an empty slot
        sem_wait(&mutex);   // Enter critical section
        
        // Add to buffer
        buffer[in] = order;
        in = (in + 1) % bufferSize;
        count++;
        
        sem_post(&mutex);   // Exit critical section
        sem_post(&full);    // Signal that a slot is filled
    }

    // Insert end marker
    Order endMarker = {0, 0, 0, true, producerID};
    
    sem_wait(&emptySlots);
    sem_wait(&mutex);
    
    buffer[in] = endMarker;
    in = (in + 1) % bufferSize;
    count++;
    
    sem_post(&mutex);
    sem_post(&full);

    file.close();
    pthread_exit(NULL); // Success
}

// The consumer thread function
void* ConsumerFunction(void* arg) {
    int producersFinished = 0;
    
    // Process orders until all producers are done
    while (producersFinished < numProducers) {
        sem_wait(&full);    // Wait for a filled slot
        sem_wait(&mutex);   // Enter critical section
        
        // Get the order from buffer (circular buffer implementation)
        Order order = buffer[out];
        out = (out + 1) % bufferSize;  // Move out pointer in circular fashion
        count--;
        
        sem_post(&mutex);   // Exit critical section
        sem_post(&emptySlots);   // Signal that a slot is now empty
        
        // Check if this is an end marker
        if (order.isEndMarker) {
            producersFinished++;
            continue;
        }
        
        // Process the order
        auto item = inventory.find(order.productID);
        
        if (item == inventory.end()) {
            // Invalid product ID - log it as rejected with "Invalid Product" description
            LogTransaction(order.customerID, order.productID, "Invalid Product", 
                          order.quantity, 0.0, false);
        } 
        else if (item->second.stock >= order.quantity) {
            // Order can be fulfilled
            double orderCost = order.quantity * item->second.price;
            item->second.stock -= order.quantity;
            LogTransaction(order.customerID, order.productID, item->second.description, 
                          order.quantity, orderCost, true);
        } 
        else {
            // Not enough stock - log it as rejected
            LogTransaction(order.customerID, order.productID, item->second.description, 
                          order.quantity, 0.0, false);
        }
    }

    pthread_exit(NULL);
}

// Parse command line arguments
void parseArguments(int argc, char* argv[]) {
    numProducers = 1;   // Default value
    bufferSize = 10;    // Default value
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            numProducers = atoi(argv[i+1]);
            i++;  // Skip the next argument
        } 
        else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            bufferSize = atoi(argv[i+1]);
            i++;  // Skip the next argument
        }
    }
    
    // Validate inputs - treat invalid values as errors
    if (numProducers < 1 || numProducers > MAX_PRODUCERS) {
        cerr << "Error: Invalid number of producers. Must be between 1 and " << MAX_PRODUCERS << "." << endl;
        exit(1);
    }
    
    if (bufferSize < 1 || bufferSize > MAX_BUFFER_SIZE) {
        cerr << "Error: Invalid buffer size. Must be between 1 and " << MAX_BUFFER_SIZE << "." << endl;
        exit(1);
    }
}


int main(int argc, char* argv[]) {
    // Parse command line arguments
    parseArguments(argc, argv);
    
    // Load the inventory
    LoadInventory();
    
    // Initialize buffer for the producer-consumer problem
    buffer = new Order[bufferSize];
    
    // Initialize semaphores for synchronization
    sem_init(&emptySlots, 0, bufferSize);  // Buffer starts empty (all slots are empty)
    sem_init(&full, 0, 0);            // Buffer starts with no filled slots
    sem_init(&mutex, 0, 1);           // Binary semaphore for mutual exclusion
    
    // Create producer and consumer threads
    pthread_t producerThreads[MAX_PRODUCERS];
    pthread_t consumerThread;
    int producerIDs[MAX_PRODUCERS];
    
    // Initialize and create producer threads
    for (int i = 0; i < numProducers; i++) {
        producerIDs[i] = i + 1;
        if (pthread_create(&producerThreads[i], NULL, ProducerFunction, &producerIDs[i]) != 0) {
            // Handle thread creation error
            // Need to make sure we don't leave other threads waiting for this one
            cerr << "Error: Failed to create producer thread " << i+1 << "." << endl;
            
            // Adjust numProducers to the number we actually created
            numProducers = i;
            
            // Skip to joining threads - don't exit immediately
            break;
        }
    }
    
    // Create consumer thread
    if (pthread_create(&consumerThread, NULL, ConsumerFunction, NULL) != 0) {
        cerr << "Error: Failed to create consumer thread." << endl;
        exit(1);
    }
    
    // Check thread return values
    void* status;
    for (int i = 0; i < numProducers; i++) {
        pthread_join(producerThreads[i], &status);
        if (status != NULL) {
            hasError = true;
        }
    }
    
    pthread_join(consumerThread, &status);
    if (status != NULL) {
        errorMessage = "Error: Consumer thread encountered an error.";
        hasError = true;
    }
    
    // Cleanup
    sem_destroy(&emptySlots);
    sem_destroy(&full);
    sem_destroy(&mutex);
    delete[] buffer;
    
    // Save updated inventory
    SaveInventory();

    // Check for any errors
    if (hasError) {
        cerr << errorMessage << endl;
        return 1;
    }
    
    cout << "Processing finished successfully, inventory and logs have been updated." << endl;
    return 0;
}
