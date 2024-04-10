#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cjson/cJSON.h"
#include "cjson/cJSON.c"
#include "stdint.h"

void json_parser(cJSON* data, char* str, int var)
{
        cJSON* obj = cJSON_GetObjectItem(data, str);
        if (var == 0)
        {
        int objValue = obj->valueint;
        printf("%s: %d\n",str, objValue);
        } 
        else
        {
        char* objStr = obj->valuestring;
        printf("%s: %s\n",str, objStr);
        }

}
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
    int length = fread(buffer, 1, sizeof(buffer), fp); 
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

    int nameValue;
    char *dataTypeValue;
    int wordValue;
    int bitValue;
    int lenValue;
    int paramsArraySize;

    int realValValue, valValue, minValValue = 0;
    int maxValValue, stepValValue, paramLenValValue, wordValValue, bitValValue;

    cJSON *testData;
    cJSON *name;
    cJSON *dataType;
    cJSON *word;
    cJSON *bit;
    cJSON *len;
    cJSON *paramsArray;

    cJSON *params;
    cJSON *realVal;
    cJSON *val;

    cJSON *minVal;
    cJSON *maxVal;
    cJSON *stepVal;

    cJSON *paramLenVal;
    cJSON *wordVal;
    cJSON *bitVal;
    cJSON *valVal;
    cJSON *strVal;

    cJSON *test1;
    cJSON *test2;
    cJSON *test3;
    char* string="\0";

    for (int i = 0; i < testDataArraySize; i++) {
        testData = cJSON_GetArrayItem(testDataArray, i);

        name = cJSON_GetObjectItem(testData, "name");
        nameValue = name->valueint;
        printf("name: %d\n", nameValue);

        dataType = cJSON_GetObjectItem(testData, "dataType");
        dataTypeValue = dataType->valuestring;
        printf("dataType: %s\n", dataTypeValue);
        
        word = cJSON_GetObjectItem(testData, "word");
        if (word != NULL) {
            wordValue = word->valueint;
            printf("word: %d\n", wordValue);
            } else {
            printf("Error: Unable to get word.\n");
            }


        bit = cJSON_GetObjectItem(testData, "bit");
        bitValue = bit->valueint;
        printf("bit: %d\n", bitValue);

        len = cJSON_GetObjectItem(testData, "len");
        lenValue = len->valueint;
        printf("len: %d\n", lenValue);

        paramsArray = cJSON_GetObjectItem(testData, "params");
        paramsArraySize = cJSON_GetArraySize(paramsArray);

        printf("paramsArraySize: %d\n", paramsArraySize);

        if( paramsArraySize == 0)
        {
            strVal = cJSON_GetObjectItem(testData, "params");
            string = strVal->valuestring;
            printf("string: %s\n", string);  
        }
        for (int j = 0; j < paramsArraySize; j++) 
            {
                params = cJSON_GetArrayItem(paramsArray, j);
                test1 = cJSON_GetObjectItem(params, "realVal");
                test2 = cJSON_GetObjectItem(params, "paramLen");
                if((strcmp(dataTypeValue, "bool")==0 || strcmp(dataTypeValue, "int")==0)&&(test1!=NULL))
                {
                    realVal = cJSON_GetObjectItem(params, "realVal");
                    realValValue = realVal->valueint;
                    if(strcmp(dataTypeValue,"bool")==0)
                    {
                        printf("realVal: %s\n", realValValue ? "true" : "false");
                    }
                    else if(strcmp(dataTypeValue,"int")==0)
                    {
                        printf("realVal: %d\n", realValValue);
                    }
            

                    valVal = cJSON_GetObjectItem(params, "val");
                    valValue = valVal->valueint;
                    printf("val: %d\n", valValue);
                } else if (paramsArraySize == 3)
                {
                    minVal = cJSON_GetObjectItem(paramsArray, "min");
                    if (minVal != NULL) {
                        minValValue = minVal->valueint;
                        printf("min: %d\n", minValValue);
                    } else {
                        printf("Error: Unable to get min value.\n");
                    }

                    maxVal = cJSON_GetObjectItem(paramsArray, "max");
                    if (maxVal != NULL) {
                        maxValValue = maxVal->valueint;
                        printf("max: %d\n", maxValValue);
                    } else {
                        printf("Error: Unable to get max value.\n");
                    }

                    stepVal = cJSON_GetObjectItem(paramsArray, "step");
                    if (stepVal != NULL) {
                        stepValValue = stepVal->valueint;
                        printf("step: %d\n", stepValValue);
                    } else {
                        printf("Error: Unable to get step value.\n");
                    }
                    j=3;
                } else if ((strcmp(dataTypeValue, "string")==0)&&(paramsArraySize!=0)&&(test2!=NULL))
                {
                    paramLenVal = cJSON_GetObjectItem(params, "paramLen");
                    paramLenValValue = paramLenVal->valueint;
                    printf("paramLen: %d\n", paramLenValValue);

                    wordVal = cJSON_GetObjectItem(params, "word");
                    wordValValue = wordVal->valueint;
                    printf("word: %d\n", wordValValue);    

                    bitVal = cJSON_GetObjectItem(params, "bit");
                    bitValValue = bitVal->valueint;
                    printf("bit: %d\n", bitValValue);

                    val = cJSON_GetObjectItem(params, "len");
                    valValue = val->valueint;
                    printf("len: %d\n", valValue); 

                } 

            }

        printf("\n");
    }

    cJSON_Delete(json);
    return 0;
}