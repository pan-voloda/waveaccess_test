#include <stdio.h>

int main() {
    int a, b, temp;
    printf("Введите a и b: ");
    scanf("%d %d", &a, &b);
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