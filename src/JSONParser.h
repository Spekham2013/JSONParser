#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define SUCCES 0
#define BUFFERSIZE 128

int8_t   settings_Open(void);
void     settings_Close(void);

int8_t settings_getString           (char* key, char* value);
int8_t settings_getInt              (char* key, int*  value);
int8_t settings_getBool             (char* key, bool*  value);

int8_t settings_getString_Array     (char* key, char (*value)[BUFFERSIZE], uint16_t* length);

int8_t settings_Single_getValue     (char* key, char*  value, bool ignoreBraces);

/**
* Function for getting values inside an array. Not to be called by user
* @param key    The key value for the value you want. Example WIFI/Scurity.
* @param value  Char array array to store values in.
* @param length Pointer that will store the return value for the length of the array.
* @return       Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_Array_getValue      (char* key, char (*value)[BUFFERSIZE], uint16_t* length);

#endif