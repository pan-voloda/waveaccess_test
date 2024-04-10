#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cjson/cJSON.h"
#include "cjson/cJSON.c"
#include "stdint.h"

int json_parser(cJSON* data, char* str)
{
    cJSON* obj = cJSON_GetObjectItem(data, str);
    int objValue = obj->valueint;
    printf("%s: %d\n",str, objValue);
    return objValue;
}

char* json_parser_str(cJSON* data, char* str)
{
    cJSON* obj = cJSON_GetObjectItem(data, str);
    char* objStr = obj->valuestring;
    printf("%s: %s\n",str, objStr);
    return objStr;
}
int main() {
    char str[] = "043200b4000000000000010000b4003b00000000100301001f0000000000000000b400b501001f003c";
    char str1[] = "\0";
    char str2[] = "\0";
    int value = 0;
    uint8_t byte[2][20];
    for(int i = 0; i <42; i++)
    {
        str1[0]=str[2*i];
        str2[0]=str[2*i+1];
        strcat(str1,str2);
        value = strtol(str1, NULL, 16);
        byte[i%2][i/2]= (uint8_t)value;
        printf("%02x ", byte[i%2][i/2]);
        if(i%2!=0) {printf("\n");}

        memset(str1, 0, sizeof(str1));
        memset(str2, 0, sizeof(str2));
    }

    FILE *fp = fopen("mc_test.json", "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
 
    char buffer[100000]; 
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

    int realValValue, valValue, minValValue, maxValValue, stepValValue, paramLenValValue, wordValValue, bitValValue;

    cJSON *testData;
    cJSON *word;
    cJSON *paramsArray;

    cJSON *params;
    cJSON *realVal;
    cJSON *val;

    cJSON *test1;
    cJSON *test2;
    char* string="\0";

    for (int i = 0; i < testDataArraySize; i++) {
        testData = cJSON_GetArrayItem(testDataArray, i);

        nameValue=json_parser(testData, "name");
        dataTypeValue=json_parser_str(testData, "dataType");
        word = cJSON_GetObjectItem(testData, "word");
        if (word != NULL) 
        {
            wordValue = word->valueint;
            printf("word: %d\n", wordValue);
        } else {
            printf("Error: Unable to get word.\n");
        }
        if(wordValue>20)
        {
            break;
        }
        bitValue=json_parser(testData, "bit");
        lenValue=json_parser(testData, "len");

        paramsArray = cJSON_GetObjectItem(testData, "params");
        paramsArraySize = cJSON_GetArraySize(paramsArray);

        printf("paramsArraySize: %d\n", paramsArraySize);

        if( paramsArraySize == 0)
        {
            string=json_parser_str(testData, "params");
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
            
                    valValue=json_parser(params, "val");

                } else if (paramsArraySize == 3&&(test1==NULL))
                {

                    minValValue=json_parser(paramsArray, "min");
                    maxValValue=json_parser(paramsArray, "max");
                    stepValValue=json_parser(paramsArray, "step");
                    j=3;
                } else if ((strcmp(dataTypeValue, "string")==0)&&(paramsArraySize!=0)&&(test2!=NULL))
                {
                    paramLenValValue=json_parser(params, "paramLen");
                    wordValValue=json_parser(params, "word");
                    bitValValue=json_parser(params, "bit");
                    valValue=json_parser(params, "len");
                } 

            }

        printf("\n");
    }

    cJSON_Delete(json);
    return 0;
}