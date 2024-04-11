#include <stdio.h>

int main() {
    unsigned int a, b, temp;
    printf("Введите a и b: ");
    scanf("%u %u", &a, &b);
    temp=a;
    while(1)
    {
        if(temp%b!=0)
        {
            temp++;
        }
        else break;
    }
    printf("%u", temp-a);
    return 0;
}