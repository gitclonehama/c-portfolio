#include "decoder.h"
#include <string.h>

/**
 * Decode an encoded string into a character stream.
 * @param encoded The input string we are decoding
 * @param decoded The output string we produce
 * @param maxLen The maximum size for decoded
 */
void decoder(const char *encoded, char *decoded, int maxLen) {
    // This is just a copy so it has something in decoded
    strncpy(decoded, encoded, maxLen);

    // Set decoded to zeros
    for (int i = 0; i < maxLen; i++) {
	    decoded[i] = 0;
    }

    // Set individual bit at index of param: bit
    void setBit(char *decoded, int maxLen, int bit) {
        int byte = bit / 8;
        if (byte < maxLen) {
            decoded[byte] |= (1 << (7 - (bit % 8)));
        }
    }
    
    int bit = 0;
    for (int i = 0; encoded[i] != '\0'; i++) {
        switch (encoded[i]) {
            case 'L':  // 000
                bit++;
                bit++;
                bit++;
                break;
            case 'E':  // 001
                bit++;
                bit++;
                setBit(decoded, maxLen, bit++);
                break;
            case 'i':  // 010
                bit++;
                setBit(decoded, maxLen, bit++);
                bit++;
                break;
            case 'q':  // 011
                bit++;
                setBit(decoded, maxLen, bit++);
                setBit(decoded, maxLen, bit++);
                break;
            case '0':  // 100
                setBit(decoded, maxLen, bit++);
                bit++;
                bit++;
                break;
            case 'Q':  // 101
                setBit(decoded, maxLen, bit++);
                bit++;
                setBit(decoded, maxLen, bit++);
                break;
            case 'h':  // 110
                setBit(decoded, maxLen, bit++);
                setBit(decoded, maxLen, bit++);
                bit++;
                break;
            case '%':  // 111
                setBit(decoded, maxLen, bit++);
                setBit(decoded, maxLen, bit++);
                setBit(decoded, maxLen, bit++);
                break;
            case '3':  // 00
                bit++;
                bit++;
                break;
            case '-':  // 01
                bit++;
                setBit(decoded, maxLen, bit++);
                break;
            case '8':  // 10
                setBit(decoded, maxLen, bit++);
                bit++;
                break;
            case 'l':  // 11
                setBit(decoded, maxLen, bit++);
                setBit(decoded, maxLen, bit++);
                break;
            default:
                break;
        }
    }
}
