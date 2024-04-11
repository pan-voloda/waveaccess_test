#include <stdio.h>

int main() {
    unsigned int arr[4], max;

    printf("Введите четыре числа: ");
    scanf("%u %u %u %u", &arr[0], &arr[1], &arr[2], &arr[3]);

    max = (arr[0] > arr[1]) ? arr[0] : arr[1];
    max = (max > arr[2]) ? max : arr[2];
    max = (max > arr[3]) ? max : arr[3];

    for(int i=0; i<4; i++)
    {
        if (max-arr[i]!=0)
        {
            printf("%u ", max-arr[i]);
        }
    }

    return 0;
}