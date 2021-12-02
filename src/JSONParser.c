#include "JSONParser.h"

// 
// Variables
// 
static uint32_t currentLine = 0;
FILE *filePointer;

// 
// Single functions
// 

/**
* This function is used to get a distinct string value from a 
* certain key. It by calling the settings_Single_getValue(..) 
* function which retrieves the string with qoutes. The 
* function then removes the qoutes and writes the value to 
* the output.
*/
int8_t settings_getString   (char* key, char* value) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[BUFFERSIZE];
    currentLine = 0;
    if (settings_Single_getValue(key, buffer, false) != SUCCES) {
        ret = -1;
    } else {
        // Seperate apostrophe from the string and then copy over
        uint8_t i = 0;
        uint8_t j = 0;
        while(buffer[i] != '\0') {
            if (buffer[i] != '"') {
                value[j++] = buffer[i];
            }
            i++;
        }
        value[j++] = '\0';

        ret = 0;
    }
    settings_Close();

    return ret;
}

/**
* This function is used to get a distinct integer value from a 
* certain key. It by calling the settings_Single_getValue(..) 
* function which retrieves the int. The function then converts
* the string to an int with the atoi function.
*/
int8_t settings_getInt      (char* key, int*  value) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[BUFFERSIZE];
    currentLine = 0;
    if (settings_Single_getValue(key, buffer, false) != SUCCES) {
        ret = -1;
    } else {
        // Convert string value to int
        *value = atoi(buffer);

        ret = 0;
    }
    settings_Close();

    return ret;
}

/**
* This function is used to get a distinct bool value from a 
* certain key. It by calling the settings_Single_getValue(..) 
* function which retrieves the bool. The function then converts
* the string to an int by checking for the presence of a letter T.
*/
int8_t settings_getBool     (char* key, bool*  value) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[BUFFERSIZE];
    currentLine = 0;
    if (settings_Single_getValue(key, buffer, false) != SUCCES) {
        ret = -1;
    } else {
        // Convert string value to bool
        if (strchr(buffer, 't') != NULL || strchr(buffer, 'T') != NULL ) {
            *value = true;
        } else {
            *value = false;
        }

        ret = 0;
    }
    settings_Close();

    return ret;
}

// 
// Array functions
// 

/**
* This function is used to get a multiple string values from a 
* certain key. It by calling the settings_Array_getValue(..) 
* function which retrieves the strings. The function then removes
* the " from the string and copies it to the output value.
*/
int8_t settings_getString_Array(char* key, char (*value)[BUFFERSIZE], uint16_t* length) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[BUFFERSIZE];
    *length = 0;

    currentLine = 0;
    if (settings_Array_getValue(key, value, length) != SUCCES) {
        ret = -1;
    } else {
        for (uint16_t row = 0; row < *length; row++) {
            // First strcpy string into buffer
            strcpy(buffer, value[row]);
            
            // Seperate apostrophe from the string and then copy over
            uint8_t i = 0;
            uint8_t j = 0;
            while(buffer[i] != '\0') {
                if (buffer[i] != '"') {
                    value[row][j++] = buffer[i];
                }
                i++;
            }
            value[row][j++] = '\0';
        }

        ret = 0;
    }
    settings_Close();

    return ret;
}

/**
* This function is used to get a multiple int values from a 
* certain key. It by calling the settings_Array_getValue(..) 
* function which retrieves the ints. The function then converts
* the strings into ints using the atoi function.
*/
int8_t settings_getInt_Array(char* key, int value[], uint16_t* length) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[BUFFERSIZE];
    char bufferBuffer[64][BUFFERSIZE];
    *length = 0;

    currentLine = 0;
    if (settings_Array_getValue(key, bufferBuffer, length) != SUCCES) {
        ret = -1;
    } else {
        for (uint16_t row = 0; row < *length; row++) {
            // First strcpy string into buffer
            strcpy(buffer, bufferBuffer[row]);
            
            int bloop = value[row];
            value[row] = atoi(buffer);
        }

        ret = 0;
    }
    settings_Close();

    return ret;
}

/**
* This function is used to get a multiple bool values from a 
* certain key. It by calling the settings_Array_getValue(..) 
* function which retrieves the bools. The function then converts
* the strings into bools by looking for the letter T.
*/
int8_t settings_getBool_Array(char* key, bool value[], uint16_t* length) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[BUFFERSIZE];
    char bufferBuffer[64][BUFFERSIZE];
    *length = 0;

    currentLine = 0;
    if (settings_Array_getValue(key, bufferBuffer, length) != SUCCES) {
        ret = -1;
    } else {
        for (uint16_t row = 0; row < *length; row++) {
            // First strcpy string into buffer
            strcpy(buffer, bufferBuffer[row]);
            
            // Convert string value to bool
            if (strchr(buffer, 't') != NULL || strchr(buffer, 'T') != NULL ) {
                value[row] = true;
            } else {
                value[row] = false;
            }
        }

        ret = 0;
    }
    settings_Close();

    return ret;
}

// 
// Initializing functions
// 

/**
* This function is used to open a file pointer
*/
int8_t settings_Open(void) {
    filePointer = fopen("/home/stephan/Documents/Synced/Projects/JSONParser/test/example.json","r");

    if (filePointer == NULL) {
        // Log: File pointer not found
        printf("Encountered ERROR");
        return -1;
    }

    return 0;
}

/**
* This function is used to close a file pointer
*/
void   settings_Close(void) {
    // Close file if pointer exists
    if (filePointer != NULL) {
        fclose(filePointer);
    }
}


// 
// getValue functions
// 

/**
* This function is used to retrieve a single string. This
* function is not be called by anyone outside this library.
* The variable ignoreBraces is used for retreiving values
* inside arrays and is only used by the settings_Array_getValue
* function.
*/
int8_t settings_Single_getValue(char* key, char* value, bool ignoreBraces) {
    char   keyword[64];
    strcpy(keyword, key);

    // Isolate keyword
    char* slashPointer = strrchr(keyword, '/');
    if (slashPointer != NULL) {
        *slashPointer = '\0';
    }

    // Find line containing keyword
    char buffer[BUFFERSIZE];

    uint8_t arrayObjectFlag = 0;
    while (fgets(buffer, sizeof(buffer), filePointer)) {
        currentLine++;

        char* pointer = strstr(buffer, keyword);

        // Prevent program of finding matching with keywords inside of objects/arrays
        if (ignoreBraces == false) {
            if (pointer == NULL && (strchr(buffer, '{') != NULL || strchr(buffer, '[') != NULL)) {
            // Prevent from triggering on first line
            if (currentLine != 1) {
                arrayObjectFlag += 1;
            }

            } else if (strchr(buffer, '}') != NULL || strchr(buffer, ']') != NULL) {
                arrayObjectFlag -= 1;
            }
        } else {
            if (strchr(buffer, ']') != NULL) {
                return -1;
            }
        }

        // Entering value extracting or entering new level
        if (pointer != NULL && arrayObjectFlag == 0) {
            // Try and find comma
            char* commaPointer = strrchr(pointer, ',');

            // Check to see if comma is not found that it isn't a false negative
            bool lastItem = false;
            if (commaPointer == NULL) {
                // Check if not last item on JSON
                fgets(buffer, sizeof(buffer), filePointer);
                
                // Check to see if there is a }
                char* bracketPointer = strrchr(buffer, '}');

                
                // Rewind to current state
                rewind(filePointer);
                for (uint32_t i = 0; i < currentLine; i++) {
                    fgets(buffer, sizeof(buffer), filePointer);
                }

                // If } is found find \n of the line
                if (bracketPointer != NULL) {
                    lastItem = true;
                    commaPointer = strrchr(buffer, '\n');
                }
            }

            if (commaPointer != NULL || lastItem) {
                // Value found
                *commaPointer = '\0';

                // Find beginning of the string
                char* colonPointer = strchr(pointer, ':');
                if (colonPointer == NULL) {
                    return -1;
                }

                // Copy over string and make sure to not change the string
                uint8_t i = 1;
                uint8_t j = 0;
                bool Apostrophe = false;
                while(colonPointer[i] != '\0') {
                    if (colonPointer[i] == '"') {
                        Apostrophe = !Apostrophe;
                    }

                    if (colonPointer[i] != ' ' || Apostrophe) {
                        value[j++] = colonPointer[i];
                    }
                    i++;
                }
                value[j++] = '\0';

                // Check to make sure the value isn't null
                if (strcmp(value, "null") == 0) {
                    return -1;
                }

                return SUCCES;

            } else {
                return settings_Single_getValue(slashPointer+1, value, false);
            }
        }
    }
    
    return -1;
}

/**
* This function is used to retrieve an array of string. This
* function is not be called by anyone outside this library.
* Do note that the buffersize must be defined otherwise it is not
* how big the buffer wil be.
*/
int8_t settings_Array_getValue(char* key, char (*value)[BUFFERSIZE], uint16_t* length) {
    uint8_t ret = -1;

    char   keyword[64];
    strcpy(keyword, key);

    // Isolate keyword
    char* slashPointer = strrchr(keyword, '/');
    if (slashPointer != NULL) {
        *slashPointer = '\0';
    }

    // Find line containing keyword
    char buffer[BUFFERSIZE];

    uint8_t  arrayObjectFlag  = 0;
    static bool enteredArray;
    if (enteredArray != true) {
        enteredArray = false;
    }

    while (fgets(buffer, sizeof(buffer), filePointer)) {
        currentLine++;

        char* pointer = strstr(buffer, keyword);
        
        // Prevent program of finding matching with keywords inside of objects/arrays
        if (pointer == NULL && (strchr(buffer, '{') != NULL || strchr(buffer, '[') != NULL)) {
            // Prevent from triggering on first line
            if (currentLine != 1) {
                arrayObjectFlag += 1;
            }
        }else if (strchr(buffer, '}') != NULL || strchr(buffer, ']') != NULL) {
            arrayObjectFlag -= 1;
        }

        // Entering value extracting or entering new level
        if (pointer != NULL && arrayObjectFlag == 0) {
            if (pointer != NULL && ((strchr(buffer, '[') != NULL) || enteredArray)) {
                // We have entered the array
                enteredArray = true;

                char* slashPointer1 = strrchr(key, '/');

                if (slashPointer1 == NULL) {
                    // Inside the correct array
                    
                    // Extracting values
                    int rowcount = 0;
                    while(fgets(buffer, sizeof(buffer), filePointer)) {
                        currentLine++;

                        char* commaPointer = strrchr(buffer, ',');

                        char* bracketPointer = strrchr(buffer, ']');
                        if (bracketPointer != NULL) {
                            *length = rowcount;

                            ret = SUCCES;
                            goto RETURN;
                        }

                        bool lastItem = false;
                        if (commaPointer == NULL) {
                            // Check if not last item on JSON
                            fgets(buffer, sizeof(buffer), filePointer);

                            // Check to see if there is a }
                            char* bracketPointer = strrchr(buffer, ']');

                            // Rewind to current state
                            rewind(filePointer);
                            for (uint32_t i = 0; i < currentLine; i++) {
                                fgets(buffer, sizeof(buffer), filePointer);
                            }

                            // If ] is found find \n of the line
                            if (bracketPointer != NULL) {
                                lastItem = true;
                                commaPointer = strrchr(buffer, '\n');
                            }
                        }

                        if (commaPointer != NULL || lastItem) {
                            // Value found
                            *commaPointer = '\0';

                            char* colonPointer = strchr(pointer, '"');
                            if (colonPointer == NULL) {
                                colonPointer = buffer;
                            }

                            // Copy over string and make sure to not change the string
                            uint8_t i = 1;
                            uint8_t j = 0;
                            bool Apostrophe = false;
                            while(colonPointer[i] != '\0') {
                                if (colonPointer[i] == '"') {
                                    Apostrophe = !Apostrophe;
                                }

                                if (colonPointer[i] != ' ' || Apostrophe) {
                                    value[rowcount][j++] = colonPointer[i];
                                }
                                i++;
                            }
                            value[rowcount][j++] = '\0';

                            // Check to make sure the value isn't null
                            if (strcmp(value[rowcount], "null") == 0) {
                                ret = -1;
                                goto RETURN;
                            }

                            rowcount++;
                        } else {
                            ret = -1;
                            goto RETURN;
                        }
                    }
                } else {
                    // If object inside array
                    char miniBuffer[BUFFERSIZE];
                        
                    uint16_t elementcounter = 0;
                    while(fgets(buffer, sizeof(buffer), filePointer)) {
                        currentLine++;

                        // Terminate string to avoid problems
                        miniBuffer[0] = '\0';

                        if (settings_Single_getValue(slashPointer+1, miniBuffer, true) == SUCCES) {
                            uint8_t i = 0;
                            uint8_t j = 0;
                            bool Apostrophe = false;

                            while(miniBuffer[i] != '\0') {
                                if (miniBuffer[i] == '"') {
                                    Apostrophe = !Apostrophe;
                                }

                                if (miniBuffer[i] != ' ' || Apostrophe) {
                                    value[elementcounter][j++] = miniBuffer[i];
                                }

                                i++;
                            }
                            value[elementcounter][j++] = '\0';

                            // Check to make sure the value isn't null
                            if (strcmp(value[elementcounter], "null") == 0) {
                                ret = -1;
                                goto RETURN;
                            }

                            elementcounter++;
                        } else {
                            if (elementcounter == 0) {
                                ret = -1;
                                goto RETURN;
                            }
                            *length = elementcounter;

                            break;
                        }

                    }
                    return SUCCES;
                }
            } else {
                if (settings_Array_getValue(slashPointer+1, value, length) == SUCCES) {
                    return SUCCES;
                } else {
                    ret = -1;
                    goto RETURN;
                }
            }
        }
    }

    RETURN:
        enteredArray = false;
        return ret;
}