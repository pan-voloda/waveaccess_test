#include <stdio.h>

int main() {
    unsigned int a, b;
    printf("\n Введите a и b: ");
    scanf("%u %u", &a, &b);
    printf("%u", b-a%b);
    return 0;
}