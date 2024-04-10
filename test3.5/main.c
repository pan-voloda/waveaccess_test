#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extractValues(char *str, int *result) {
    int i, j;
    char temp[5]; // Временный массив для хранения четырех символов строки
    for (i = 0, j = 0; i < strlen(str); i += 4, j++) {
        strncpy(temp, &str[i], 4); // Копируем четыре символа во временный массив
        temp[4] = '\0'; // Добавляем нуль-терминатор
        result[j] = strtol(temp, NULL, 16); // Преобразуем строку в шестнадцатеричном формате в int
    }
}

int main() {
    char str[] = "043200b4000000000000010000b4003b00000000100301001f0000000000000000b400b501001f003c";
    int result[20]; // Массив для хранения результата

    extractValues(str, result);

    printf("Результат:\n");
    for (int i = 0; i < 21; i++) {
        printf("%04x ", result[i]); // Выводим каждый элемент массива как четырехзначное шестнадцатеричное число
    }
    printf("\n");

    return 0;
}