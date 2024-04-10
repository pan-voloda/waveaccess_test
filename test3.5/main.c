#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdint.h"

int main() {
    char str[] = "043200b4000000000000010000b4003b00000000100301001f0000000000000000b400b501001f003c";
    char str_x[4]="\0";
    char* value;
    uint16_t bytes[20];
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 4; j++)
        {   
            strcat(&str_x[j],&str[4*i+j]);
        }
        printf("string: %s\n", str_x);
        memset(str_x, 0, sizeof(str_x));
    }
    return 0;
}