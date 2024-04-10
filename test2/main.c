#include <stdio.h>

int main() {
    int a, b, temp;
    printf("Введите a и b: ");
    scanf("%d %d", &a, &b);
    temp=a;
    while(1)
    {
        if(a%b!=0)
        {
            a++;
        }
        else break;
    }
    printf("%d", a-temp);
    return 0;
}