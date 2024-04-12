#include <stdio.h>

int main() {
    unsigned int arr[4], max;

    printf("Введите четыре числа: ");
    scanf("%u %u %u %u", &arr[0], &arr[1], &arr[2], &arr[3]);
    max=arr[0];
    for(int i=1; i<=3; i++)
    {
    max = (max > arr[i]) ? max : arr[i];
    }

    for(int i=0; i<4; i++)
    {
        if (max-arr[i]!=0)
        {
            printf("%u ", max-arr[i]);
        }
    }

    return 0;
}