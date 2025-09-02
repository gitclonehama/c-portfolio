#include <iostream>
#include <string>
#include <cmath>   // For std::pow() function
#include <cctype>   // For std::isxdigit() 

int main(int argc, char* argv[])
{
	// Check the number of parameters (from cplusplus.com)
	if (argc < 2)
	{
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " HEX ADDRESS" << std::endl;
		return 1;   // Error
	}

	// Extract hex address
	std::string hexAddress = argv[1];
	
	// Check if all chars from input are valid hex
	for (auto ch : hexAddress)    // C++ foreach loop
	{
		if (std::isxdigit(ch) == false)
		{
			std::cerr << "Error! Please ensure all inputs are valid hex digits." << std::endl;
			return 2;   // Error
		}
	}		

	// Calculate sizes
	int hexLength = hexAddress.size();
	int addressSize = hexLength * 4;
	long long memorySize = std::pow(2, addressSize);   // 2^(addressSize)


	// Result output
	std::cout << "Address Size: " << addressSize << " bits\n";
	std::cout << "Memory Size: " << memorySize << " bytes\n";
	
	return 0;
}


/*
References:

Search on "how to raise a number to a power in C++"
https://stackoverflow.com/questions/845912/what-is-the-c-function-to-raise-a-number-to-a-power

Search on "Hex validation in C++"
https://cplusplus.com/reference/cctype/isxdigit/

Article from assignment PDF to get started
https://cplusplus.com/articles/DEN36Up4/
*/
