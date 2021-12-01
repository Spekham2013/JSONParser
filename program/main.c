#include <stdbool.h>

#include "../src/JSONParser.h"

int main() {
    char  buffer[16][BUFFERSIZE];

    uint16_t length;

    settings_getString_Array("phoneNumbers/type", *buffer, &length);

    return 0;
}
