#include <stdio.h>

int main() {
    unsigned long a, b, temp;
    printf("Введите a и b: ");
    scanf("%lu %lu", &a, &b);
    temp=a;
    while(1)
    {
        if(temp%b!=0)
        {
            temp++;
        }
        else break;
    }
    printf("%d", temp-a);
    return 0;
}