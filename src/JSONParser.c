#include "JSONParser.h"

FILE *filePointer;

// TODO: Convert to static variable
uint32_t settings_FileLines;

int main() {
    char buffer[64];
    
    settings_getString("firstName", buffer);
    printf(buffer);

    return 0;
}

int8_t settings_Open(void) {
    settings_FileLines = 0;
    filePointer = fopen("/home/stephan/Documents/Synced/Studie/Jaar_4/Blok_1/Project/5G-corona/Firmware/settingsParser/lib/JSONParser/test/src","r");

    if (filePointer == NULL) {
        // Log: File pointer not found
        printf("Encountered ERROR");
        return -1;
    }

    // Get the amount of lines in the file
    char buffer[BUFFERSIZE];
    while(fgets(buffer, sizeof(buffer), filePointer) != NULL) {
        settings_FileLines++;
    }
    rewind(filePointer);

    return 0;
}

void   settings_Close(void) {
    settings_FileLines = 0;

    // Close file if pointer exists
    if (filePointer != NULL) {
        fclose(filePointer);
    }
}

int8_t settings_getString   (char* key, char* value) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[128];
    if (settings_Single_getValue(key, buffer, 0) != SUCCES) {
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

int8_t settings_getInt      (char* key, int*  value) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[128];
    if (settings_Single_getValue(key, buffer, 0) != SUCCES) {
        ret = -1;
    } else {
        // Convert string value to int
        *value = atoi(buffer);

        ret = 0;
    }
    settings_Close();

    return ret;
}

int8_t settings_getBool     (char* key, bool*  value) {
    int8_t ret = -1;

    // Open file
    if (settings_Open() != SUCCES) {
        // Log: File couldn't be openend
        return ret;
    }

    char buffer[128];
    if (settings_Single_getValue(key, buffer, 0) != SUCCES) {
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

int8_t settings_Single_getValue(char* key, char* value, uint32_t atLine) {
    char   keyword[64];
    strcpy(keyword, key);

    // Isolate keyword
    char* slashPointer = strrchr(keyword, '/');
    if (slashPointer != NULL) {
        *slashPointer = '\0';
    }

    // Find line containing keyword
    char buffer[BUFFERSIZE];

    uint32_t currentLine = atLine;
    uint8_t arrayObjectFlag = 0;
    while (fgets(buffer, sizeof(buffer), filePointer)) {
        currentLine++;

        char* pointer = strstr(buffer, keyword);

        // Prevent program of finding matching with keywords inside of objects/arrays
        if (pointer == NULL && (strchr(buffer, '{') != NULL || strchr(buffer, '[') != NULL)) {
            // Prevent from triggering on first line

            // TODO: Fix and check for first {
            if (currentLine != 1) {
                arrayObjectFlag += 1;
            }
        }

        if (strchr(buffer, '}') != NULL || strchr(buffer, ']') != NULL) {
            arrayObjectFlag -= 1;
        }

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

                // Check to make sure the value isn't null
                if (strcmp(value, "null") == 0) {
                    return -1;
                }

                return SUCCES;

            } else {
                return settings_Single_getValue(slashPointer+1, value, currentLine);
            }
        }
    }
    
    return -1;
}