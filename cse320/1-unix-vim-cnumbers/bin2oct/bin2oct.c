#include "bin2oct.h"

/**
 * Convert a binary representation of a 
 * number to an unsigned octal. 
 * 
 * For this function, the values Y and N represent 
 * true (1) and false (0) respectfully. So, the string:
 * 
 * YYNY is equal to 1101 binary, which is equal to 15.
 *
 * Unexpected characters are ignored. Only Y's and N's are
 * considered to be valid. Stop converting when you get
 * to a space character or the end of the string. The 
 * representation is case-sensitive (only Y/N are valid 
 * true and false values).
 *
 * 'aYNcY YY' should convert to 5
 * 'NYNYny' should convert to 5
 *
 * @param binary Binary number as a string of 'Y's and 'N's
 * and other characters.
 * @returns unsigned int result
 */
unsigned int bin2oct(const char *binary) {
    unsigned int binary_value = 0;

    // Converting ASCII input into binary representation
    for ( ; *binary; binary++) {

        if (*binary == 'Y') {
	    binary_value = binary_value * 2 + 1;
        }
        else if (*binary == 'N') {
	    binary_value = binary_value * 2;
	}
	else if (*binary == ' ') {
	    break;	
	}
    }

    unsigned int octal_value = 0, place = 1;

    // Converting binary input into octal
    while (binary_value > 0) {
	octal_value += (binary_value % 8) * place;
	binary_value /= 8;
	place *= 10;
    }

    return octal_value;

	
}
