#include <stdio.h>

long first(long);
long second(long, long);
long min(long, long);

int main() 
{
    long value = 27;
    long result = first(value);
    printf("first(%ld) = %ld\n", value, result);
    
    result = second(12, 22);
    printf("second(12,22) = %ld\n", result);

    result = min(12, -3);
    printf("min(12,-3) = %ld\n", result);

    result = min(73, 12);
    printf("min(12,22) = %ld\n", result);

    result = min(-14, -69);
    printf("min(-14,-69) = %ld\n", result);


    return 0;
}


