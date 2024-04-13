#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cjson/cJSON.h"
#include "cjson/cJSON.c"
#include "stdint.h"

int json_parser(cJSON* data, char* str)
{
    cJSON* obj = cJSON_GetObjectItem(data, str);
    return obj->valueint;
}
int bits1(int len)
{
    return (1 << len) - 1;
}
char* json_parser_str(cJSON* data, char* str)
{
    cJSON* obj = cJSON_GetObjectItem(data, str);
    return obj->valuestring;
}

void extract_words(char *str, uint16_t *result) {
    int i, j;
    char temp[5]; 
    for (i = 0, j = 0; i < strlen(str); i += 4, j++) {
        strncpy(temp, &str[i], 4); 
        temp[4] = '\0'; 
        result[j] = strtol(temp, NULL, 16); 
    }
}

int main() {
    char str[] = "043200b4000000000000010000b4003b00000000100301001f0000000000000000b400b501001f003c043200b4000000000000010000b4003b00000000100301001f0000000000000000b400b501001f003c";
    uint16_t words[45];
    extract_words(str, words);

    printf("Результат:\n");
    for (int i = 0; i < 45; i++) {
        printf("%04x ", words[i]); 
    }
    printf("\n");
    
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
    } 

    cJSON *testDataArray = cJSON_GetObjectItem(json, "TestData");
    int testDataArraySize = cJSON_GetArraySize(testDataArray);

    int nameValue;
    int wordValue;
    int bitValue;
    int lenValue;
    int realValValue;
    int valValue;
    int paramsArraySize;
    int paramLenValValue;
    int minValValue;
    int maxValValue;
    int stepValValue;
    int someval;
    int mask;  

    char *dataTypeValue;   
    char* string;

    cJSON *testData;
    cJSON *word;
    cJSON *paramsArray;

    cJSON *params;
    cJSON *realVal;
    cJSON *val;

    cJSON *test1;
    cJSON *test2;

    uint16_t cmd = 0;
    uint16_t cmd_str = 0;
    
    for (int i = 0; i < testDataArraySize; i++) {
        testData = cJSON_GetArrayItem(testDataArray, i);

        nameValue=json_parser(testData, "name");
        printf("Name_%d: ", nameValue);
        dataTypeValue=json_parser_str(testData, "dataType");
        word = cJSON_GetObjectItem(testData, "word");
        if (word != NULL) 
        {
            wordValue = word->valueint;
        } else {
            printf("Error: Unable to get word.\n");
        }

        cmd = words[wordValue-1];
        bitValue=json_parser(testData, "bit");
        lenValue=json_parser(testData, "len");

        cmd = cmd >> (16-(bitValue+lenValue));
        mask = bits1(lenValue);
        cmd = cmd & mask;

        paramsArray = cJSON_GetObjectItem(testData, "params");
        paramsArraySize = cJSON_GetArraySize(paramsArray);

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
                    realValValue = json_parser(params, "realVal");
                    valValue=json_parser(params, "val");

                    if(valValue==cmd)
                    {
                    if(strcmp(dataTypeValue,"bool")==0)
                    {
                        printf("%s\n", realValValue ? "true" : "false");
                    }
                    else if(strcmp(dataTypeValue,"int")==0)
                    {
                        printf("%d\n", realValValue);
                    }
                        
                    }

                } else if (paramsArraySize == 3&&(test1==NULL))
                {

                    minValValue=json_parser(paramsArray, "min");
                    maxValValue=json_parser(paramsArray, "max");
                    stepValValue=json_parser(paramsArray, "step");
                    someval = minValValue;
                    for(int i = 0; i<cmd; i++)
                    {
                        someval+=stepValValue;
                        if(someval>=maxValValue)
                        {
                            someval=minValValue+(someval-maxValValue);
                        }
                    }
                    printf("%d\n", someval);
                    j=3;
                } else if ((strcmp(dataTypeValue, "string")==0)&&(paramsArraySize!=0)&&(test2!=NULL))
                {
                    paramLenValValue=json_parser(params, "paramLen");
                    wordValue=json_parser(params, "word");
                    bitValue=json_parser(params, "bit");
                    lenValue=json_parser(params, "len");

                    mask = bits1(lenValue+(8-bitValue));
                    cmd_str = words[wordValue-1] & mask;
                    cmd_str = cmd_str >> (16-(lenValue+bitValue));
                    printf("substring: %02x\n", cmd_str);
                } 

            }

        printf("\n");
    }

    cJSON_Delete(json);
    return 0;
}