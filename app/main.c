#include <stdbool.h>

#include "../src/JSONParser.h"

int main() {
    char buffer[16][settingsBUFFERSIZE];
    uint16_t length;

    settings_configureFilePath("/home/stephan/Documents/Synced/Projects/git/JSONParser/test/example.json");

    settings_getString_Array("address/phoneNumbers/number", *buffer, &length);

    // int8_t errorCode = settings_getInt_Array("ChildrenAge", buffer, &length);

    return 0;
}
