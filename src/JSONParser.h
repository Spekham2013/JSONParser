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

int8_t settings_getString   (char* key, char* value);
int8_t settings_getInt      (char* key, int*  value);
int8_t settings_getBool     (char* key, bool*  value);

int8_t settings_Single_getValue   (char* key, char* value, uint32_t atLine);
// int8_t settings_Array_getValue    (char* key, char* value, uint32_t atLine);

#endif