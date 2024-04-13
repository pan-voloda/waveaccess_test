#include <stdio.h>

int main() {
    unsigned int a, b, temp;
    printf("Введите a и b: ");
    scanf("%u %u", &a, &b);
    temp=a;
    while(temp%b!=0)
    {
        temp++;
    }
    printf("%u", temp-a);
    return 0;
}