#include <iostream>
#include <unistd.h>	// for access(), open() and close()
#include <fcntl.h> 	// for syscall flags
#include <vector>	// for buffers


/// @brief Takes in an input file and a destination file with option parameters
/// -b <int> (buffer size), -t (truncate mode), -a (append mode)
/// @param argc The count of arguments given
/// @param argv list of arguments delimited by space
/// @return 0 on success and 1 on error
int main(int argc, char* argv[])
{
	// Default values
	int buffSize = 64;
	bool aMode = false;
	bool tMode = false;
	std::string fileIn;
	std::string fileOut;
	
	// Check the number of parameters
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " fileIn fileOut" << std::endl;
		return 0;
	}

	// Iterate over all cli args (skipping arg[0])
	// and handle all possible input arguments
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		
		// Handle -b arg
		if (arg == "-b")
		{
			// All "-b" parameters must be followed by additional input
			// check if the additional input index is out of argv bounds
			if (i + 1 >= argc)		
			{
				std::cerr << "Error: Could not find size argument for option -b. " << std::endl << "Usage: fileIn fileOut -b 64" << std::endl;
				return 1;
			}
			// We now have to validate the number provided following -b param
			std::string buffSizeStr = argv[i + 1];

			for (auto ch : buffSizeStr)
			{
				if (!isdigit(ch))	// Check if character is NOT a digit
				{
					std::cerr << "Error: Buffer size must be a positive int. Given: " << buffSizeStr << std::endl;
					return 1;
				}
			}

			// Convert to integer
			buffSize = std::stoi(argv[i + 1]);

			// Ensure given buffSize is positive
			if (buffSize <= 0)
			{
				std::cerr << "Error: Buffer size must be greater than 0. Given: " << buffSizeStr << std::endl;
				return 1;
			}
			
			i++;									// Skip the next arg since we just processed it
		}
		// Handle -a arg
		else if (arg == "-a")
		{
			aMode = true;
		}
		// Handle -t arg
		else if (arg == "-t")
		{
			tMode = true;
		}
		// If its none of the above, it has to be a file name
		// Handle file name args
		else 
		{
			// We expect to receive fileIn first
			if (fileIn.empty())
			{
				fileIn = arg;
			}
			// If we already saw fileIn, must be fileOut
			else if (fileOut.empty())
			{
				fileOut = arg;
			}
			// If we have values for fileIn and fileOut, error
			else
			{
				std::cerr << "Error: Too many file names received." << std::endl;
				return 1;
			}
		}
	}

	// After loop, we should at least have a fileIn and fileOut
	// so we check if either of them are empty and throw an error if 
	// any of the file variables are empty
	if (fileIn.empty() || fileOut.empty())
	{
		std::cerr << "Error: Missing one or both file parameters." << std::endl;
		return 1;
	}

	
	// Handle opening fileIn in read-only mode
	const char *inPathName = fileIn.c_str();	// open() expects a c_str formated file name
	int inFlags = O_RDONLY;
	mode_t inPerms = 0;		// Default permissions

	// Open fileIn given parameters above
	int inFD = open(inPathName, inFlags, inPerms);
	if (inFD == -1)
	{
		std::cerr << "Error opening source file." << std::endl;
		return 1;
	}


	// Handle opening fileOut with user specified params
	const char *outPathName = fileOut.c_str();

	// For the destination file, we want to only allow
	// calling this program on existing files if -t or -a are given.
	if (access(outPathName, F_OK) == 0)		// If destination file exists
	{
		if (!aMode && !tMode)
		{
			std::cerr << "Error: Destination file '" << fileOut << "' already exists. Use -a to append or -t to truncate the file." << std::endl;
			close(inFD);	// Ensure we close the previously opened source file
			return 1;
		}
	}

	int outFlags = O_WRONLY | O_CREAT;			// Open for write, create if doesn't exit
	// Add more flags based on options selected by given params
	if (tMode)									// Check for "-t"
	{
		outFlags |= O_TRUNC;					// Truncate file
	}
	if (aMode)									// Check for "-a"
	{
		outFlags |= O_APPEND;					// Append to file
	}

	// Warn user that append will take precedance if both -t and -a are given
	if (tMode && aMode)
	{
		std::cerr << "ERROR: Both -a and -t were given." << std::endl;
		return 1;
	}
	
	mode_t outPerms = S_IRUSR | S_IWUSR;		// User read, user write
	
	// Open fileOut given parameters above
	// then check for error
	int outFD = open(outPathName, outFlags, outPerms);
	if (outFD == -1)
	{
		std::cerr << "Error opening source file." << std::endl;
		return -1;
	}


	// Now we handle reading and writing to the opened files
	std::vector<char> buffer(buffSize);

	ssize_t readBytes;
	while ((readBytes = read(inFD, buffer.data(), buffSize)) > 0)
	{
		// Write read bytes to outFD
		ssize_t writtenBytes = write(outFD, buffer.data(), readBytes);

		// Ensure bytes written are equavalent to bytes read
		// If we find that they are not, we return error and close the files
		if (writtenBytes != readBytes)
		{
			std::cerr << "Error writing to destination file." << std::endl;
			close(inFD);
			close(outFD);
			return 1;
		}
	}

	// Now we can check the values of readBytes
	// where we expect a positive value (error returns -1)
	if (readBytes == -1)
	{
		std::cerr << "Error reading from source file." << std::endl;
		close(inFD);
		close(outFD);
		return 1;
	}

	// If no error until now, we can close the files and again
	// ensure the close() exacutes without any issues
	if (close(inFD) == -1)
	{
		std::cerr << "Error closing source file." << std::endl;
		return 1;
	}
	if (close(outFD))
	{
		std::cerr << "Error closing destination file." << std::endl;
		return 1;
	}

	// Hurray! Files were opened, read, written, and close with sucess!
	std::cout << "Operations successful!" << std::endl;
	return 0;
}


/*
Works Cited:

Reading about switch statements:
- https://www.w3schools.com/cpp/cpp_switch.asp

Learning about std::cerr:
- https://stackoverflow.com/questions/23813144/c-error-expression-must-have-integral-or-enum-type

Reading about open(), close(), read(), write() system calls
- https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
- https://www.geeksforgeeks.org/system-call-in-c/#
- https://man7.org/linux/man-pages/man2/open.2.html

Reading about stoi validation:
- https://cplusplus.com/reference/string/stoi/

*/
