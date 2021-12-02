#include <stdbool.h>

#include "../src/JSONParser.h"

int main() {
    int  buffer[16];

    uint16_t length;

    int8_t errorCode = settings_getInt_Array("ChildrenAge", buffer, &length);

    return 0;
}
