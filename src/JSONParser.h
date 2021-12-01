#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define SUCCES 0
#define BUFFERSIZE 128

// 
// Functions for users
// 

int8_t settings_getString           (char* key, char* value);
int8_t settings_getInt              (char* key, int*  value);
int8_t settings_getBool             (char* key, bool*  value);

// TODO: Add int and bool versions
int8_t settings_getString_Array     (char* key, char (*value)[BUFFERSIZE], uint16_t* length);


// 
// Initializing functions
// 

/**
* Function to open file pointer to file.
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t   settings_Open(void);

/**
* Function to close file pointer to file.
* @return Returns 0 for SUCCES and -1 for failure. (can't fail however).
*/
void     settings_Close(void);

// 
// Getting value functions
// 

/**
* Function for getting distinct values. Not to be called by user
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Char array to store value in.
* @param ignoreBraces Variable to allow braces to be ingnored. Only to be used by array functions
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_Single_getValue     (char* key, char*  value, bool ignoreBraces);

/**
* Function for getting values inside an array. Not to be called by user
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Char array array to store values in.
* @param length Pointer that will store the return value for the length of the array.
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_Array_getValue      (char* key, char (*value)[BUFFERSIZE], uint16_t* length);

#endif