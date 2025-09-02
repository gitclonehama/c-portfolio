#include <iostream>
#include <iomanip>
#include <fstream>
#include <pthread.h>
#include <map>
#include <vector>
#include <string>

using namespace std;


/*
Example inventory.old:
100492 2.50 360 Northern Red Oak
201005 10.17 62 Shagbark Hickory
100305 1.95 1043 Sugar Maple
100491 2.50 803 White Oak
*/
struct InventoryItem {
    unsigned int productID;
    double price;
    unsigned int stock;
    string description;
};


/*
Example orders file:
9981532 100305 65
9981532 100492 40
0003183 100305 100
9981532 100492 25
0003183 201005 5
0050600 100305 60
*/
struct Order {
    unsigned int customerID;
    unsigned int productID;
    unsigned int quantity;
};

// Program variables
map<unsigned int, InventoryItem> inventory;     // Stores inventory data
vector<Order> orders;                           // Stores orders data


// Function to open inventory.old, extract values, store the values in inventory map, close file
void LoadInventory() {
    ifstream file("inventory.old");

    // Ensure file opens successfully (permission or existace)
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
        inventory[id] = {id, price, stock, desc};   // Store item in map
    }

    file.close();    // Close the file
    
}


// Save the updates to inventory.new
void SaveInventory() {
    // Create new inventory
    ofstream file("inventory.new");
    // Ensure file is created successfully
    if(!file) {
        cerr << "Error: Could not create new inventory file." << endl;
        return;
    }

    // Loop through inventory map, pass each instance as const reference (cannot change, memory efficient)
    for (const auto& item : inventory) {
        // item.second => the value part of item in map
        file << item.second.productID << " " << item.second.price 
        << " " << item.second.stock << " " << item.second.description << "\n";
    }

    file.close();
}


// Save transactions into file "log"
void LogTransaction(unsigned int customerID, unsigned int productID, string productDescription, unsigned int quantity, double transactionAmount, bool result) {
    ofstream logFile("log", ios::app);
    // Ensure "log" was successfully opened / created
    if (!logFile) {
        cerr << "Error: Could not create log file." << endl;
        return;
    }
    
    logFile << right << setfill('0') << setw(7) << customerID << " "  // 7-digit customer ID
            << setw(6) << productID << " "                           // 6-digit product ID
            << left << setfill(' ') << setw(30) << productDescription << " "  // 30-character description, left-aligned
            << right << setw(5) << quantity << "  "                  // 5-digit quantity, right-aligned
            << left << "$" << setw(9) << fixed << setprecision(2) << transactionAmount << " "  // Money field
            << (result ? "filled" : "rejected") << endl;

    logFile.close();
}


// The producer thread function: reads `orders` file and stores orders in a vector
void* ProducerFunction(void* arg) {
    ifstream file("orders");
    // Ensure file was opened successfully
    if (!file) {
        cerr << "Error: Could not open orders file." << endl;
        pthread_exit(NULL);
    }

    // Extract order attributes
    unsigned int customerID, productID, quantity;
    while (file >> customerID >> productID >> quantity) {
        // Append order object to the vector of orders
        orders.push_back({customerID, productID, quantity});
    }

    // Close the file
    file.close();
    // Exit thread
    pthread_exit(NULL);
}


// The consumer thread function: processes the orders and adds them to log file
void* ConsumerFunction(void* arg) {
    // Loop through orders
    for (const auto& order : orders) {
        // Find item from inventory
        auto item = inventory.find(order.productID);    // returns end() if not found
        
        // Non existant items in order constitute an error (edstem #196)
        if (item == inventory.end()) {
            cerr << "Error: Invalid product ID in order." << endl;
            pthread_exit((void*)-1);  // Return error status
        }
        
        // Validate that we have enough stock to fill order
        if (item->second.stock >= order.quantity) {
            // Order can be fulfilled

            // Calculate order cost
            double orderCost = order.quantity * item->second.price;
            // Subtract from stock
            item->second.stock -= order.quantity;
            // Log successfull transaction
            LogTransaction(order.customerID, order.productID, item->second.description, order.quantity, orderCost, true);
        } else {
            // Order cannot be fulfilled
            // Log order with reject (Handled by LogTransaction)
            LogTransaction(order.customerID, order.productID, item->second.description, order.quantity, 0.0, false);
        }
    }

    // Exit pthread
    pthread_exit(NULL);
}


int main ()  {
    // Load the inventory
    LoadInventory();

    // Create producer and consumer threads
    pthread_t  producerThread, consumerThread;

    // Create and run producer thread
    pthread_create(&producerThread, NULL, ProducerFunction, NULL);
    pthread_join(producerThread, NULL);     // Wait for producer

    // Create and run consumer thread
    void* consumerStatus = NULL;
    pthread_create(&consumerThread, NULL, ConsumerFunction, NULL);
    pthread_join(consumerThread, &consumerStatus);     // wait for consumer and get status

    // Check if consumer thread ended with error
    if (consumerStatus != NULL) {
        cerr << "Error: Consumer thread encountered an error." << endl;
        return 1;  // Exit program with error status
    }

    // Finally, finish by saving inventory.new
    SaveInventory();
    cout << "Processing finished successfully, inventory and logs have been updated." << endl;
    
    return 0;
}



/*
REFERENCES

Learning more about pthread libaray in C++:
 - https://www.geeksforgeeks.org/thread-functions-in-c-c/

 Learning more about formatting in C++:
 - https://www.geeksforgeeks.org/formatted-i-o-in-c/

*/