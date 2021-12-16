#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define SUCCES 0
#define BUFFERSIZE 128

#define SETTINGSFILE "/home/stephan/Documents/Synced/Projects/JSONParser/test/example.json"

// 
// Functions for users
// 

/**
* @brief Function for getting a specific string value
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Char array to store value in.
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_getString           (char* key, char* value);

/**
* @brief Function for getting a specific int value
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Pointer to int. 
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_getInt              (char* key, int*  value);

/**
* @brief Function for getting a specific bool value
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Pointer to boolean. 
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_getBool             (char* key, bool*  value);

/**
* Function for getting array of strings
* @param key The key value for the value you want. Example WIFI/Security.
* @param value String array to store value in.
* @param length Variable to store the length of the array.
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_getString_Array     (char* key, char  (*value)[BUFFERSIZE], uint16_t* length);

/**
* @brief Function for getting array of Ints
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Int array to store value in.
* @param length Variable to store the length of the array.
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_getInt_Array        (char* key, int     value[], uint16_t* length);

/**
* @brief Function for getting array of Bool
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Bool array to store value in.
* @param length Variable to store the length of the array.
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_getBool_Array       (char* key, bool    value[], uint16_t* length);


// 
// Initializing functions
// 

/**
* @brief Function to open file pointer to file.
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t   settings_Open(void);

/**
* @brief Function to close file pointer to file.
* @return Returns 0 for SUCCES and -1 for failure. (can't fail however).
*/
void     settings_Close(void);

// 
// Getting value functions
// 

/**
* @brief Function for getting distinct values. Not to be called by user
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Char array to store value in.
* @param ignoreBraces Variable to allow braces to be ingnored. Only to be used by array functions
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_Single_getValue     (char* key, char*  value, bool ignoreBraces);

/**
* @brief Function for getting values inside an array. Not to be called by user
* @param key The key value for the value you want. Example WIFI/Security.
* @param value Char array array to store values in.
* @param length Pointer that will store the return value for the length of the array.
* @return Returns 0 for SUCCES and -1 for failure.
*/
int8_t settings_Array_getValue      (char* key, char (*value)[BUFFERSIZE], uint16_t* length);

#endif