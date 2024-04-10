#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cjson/cJSON.h"
#include "cjson/cJSON.c"
#include "stdint.h"

int main() {
    char str[] = "043200b4000000000000010000b4003b00000000100301001f0000000000000000b400b501001f003c";
    char str1[] = "\0";
    char str2[] = "\0";
    int value = 0;
    uint8_t byte[2][36];
    for(int i = 0; i <72; i++)
    {
        str1[0]=str[2*i];
        str2[0]=str[2*i+1];
        strcat(str1,str2);
        // printf("%s \n", str1);
        value = strtol(str1, NULL, 16);
        byte[i%2][i/2]= (uint8_t)value;
        // printf("%02x ", byte[i%2][i/2]);
        // if(i%2!=0) {printf("\n");}

        memset(str1, 0, sizeof(str1));
        memset(str2, 0, sizeof(str2));
    }
    // open the file 
    FILE *fp = fopen("mc_test.json", "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
 
    char buffer[1048576]; 
    int len = fread(buffer, 1, sizeof(buffer), fp); 
    fclose(fp); 
  
    cJSON *json = cJSON_Parse(buffer); 
    if (json == NULL) { 
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        cJSON_Delete(json); 
        return 1; 
    } else printf("Parsed successfully\n"); 

    cJSON *testDataArray = cJSON_GetObjectItem(json, "TestData");
    int testDataArraySize = cJSON_GetArraySize(testDataArray);

    for (int i = 0; i < testDataArraySize; i++) {
        cJSON *testData = cJSON_GetArrayItem(testDataArray, i);

        cJSON *name = cJSON_GetObjectItem(testData, "name");
        int nameValue = name->valueint;
        printf("name: %d\n", nameValue);

        cJSON *dataType = cJSON_GetObjectItem(testData, "dataType");
        char *dataTypeValue = dataType->valuestring;
        printf("dataType: %s\n", dataTypeValue);

        cJSON *word = cJSON_GetObjectItem(testData, "word");
        int wordValue = word->valueint;
        printf("word: %d\n", wordValue);

        cJSON *bit = cJSON_GetObjectItem(testData, "bit");
        int bitValue = bit->valueint;
        printf("bit: %d\n", bitValue);

        cJSON *len = cJSON_GetObjectItem(testData, "len");
        int lenValue = len->valueint;
        printf("len: %d\n", lenValue);

        cJSON *paramsArray = cJSON_GetObjectItem(testData, "params");
        int paramsArraySize = cJSON_GetArraySize(paramsArray);

        for (int j = 0; j < paramsArraySize; j++) {

            if(paramsArraySize == 3)
            {
            cJSON *params = cJSON_GetArrayItem(paramsArray, j);

            cJSON *realVal = cJSON_GetObjectItem(params, "realVal");
            int realValValue = realVal->valueint;
            printf("realVal: %s\n", realValValue ? "true" : "false");

            cJSON *val = cJSON_GetObjectItem(params, "val");
            int valValue = val->valueint;
            printf("val: %d\n", valValue);
            } else if (paramsArraySize == 3)
            {
            cJSON *params = cJSON_GetArrayItem(paramsArray, j);

            cJSON *minVal = cJSON_GetObjectItem(params, "min");
            int minValValue = minVal->valueint;
            printf("min: %d\n", minValValue);

            cJSON *maxVal = cJSON_GetObjectItem(params, "max");
            int maxValValue = maxVal->valueint;
            printf("max: %d\n", maxValValue);

            cJSON *stepVal = cJSON_GetObjectItem(params, "step");
            int stepValValue = stepVal->valueint;
            printf("step: %d\n", stepValValue);
            } else if (paramsArraySize == 4)
            {
            cJSON *params = cJSON_GetArrayItem(paramsArray, j);

            cJSON *paramLenVal = cJSON_GetObjectItem(params, "paramLen");
            int paramLenValValue = paramLenVal->valueint;
            printf("paramLen: %d\n", paramLenValValue);

            cJSON *wordVal = cJSON_GetObjectItem(params, "word");
            int wordValValue = wordVal->valueint;
            printf("word: %d\n", wordValValue);    

            cJSON *bitVal = cJSON_GetObjectItem(params, "bit");
            int bitValValue = bitVal->valueint;
            printf("bit: %d\n", bitValValue);

            cJSON *val = cJSON_GetObjectItem(params, "len");
            int valValue = val->valueint;
            printf("len: %d\n", valValue); 

            } else if (paramsArraySize == 1)
            {
            cJSON *params = cJSON_GetArrayItem(paramsArray, j);
            cJSON *strVal = cJSON_GetObjectItem(params, "");
            char* string = strVal->valuestring;
            printf("string: %s\n", string);  
            }

        }

        printf("\n");
    }

    cJSON_Delete(json);
    return 0;
}