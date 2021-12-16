#include <stdbool.h>

#include "../src/JSONParser.h"

int main() {
    int  buffer[16];

    uint16_t length;

    settings_configureFilePath("/home/stephan/Documents/Synced/Projects/JSONParser/test/example.json");

    int8_t errorCode = settings_getInt_Array("ChildrenAge", buffer, &length);

    return 0;
}
