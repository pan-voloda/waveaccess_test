#include <stdio.h>

int main() {
    int arr[4], max;

    printf("Введите четыре числа: ");
    scanf("%d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3]);
    
    max = (arr[0] > arr[1]) ? arr[0] : arr[1];
    max = (max > arr[2]) ? max : arr[2];
    max = (max > arr[3]) ? max : arr[3];
    
    for(int i = 0; i < 3; ++i)
    {
        for(int j = i+1; j < 4; ++j)
        {
            if(arr[i]==arr[j])
        }
    }
    
    for(int i=0; i<4; i++)
    {
        if (max-arr[i]!=0)
        {
            printf("%d ", max-arr[i]);
        }
    }

    return 0;
}