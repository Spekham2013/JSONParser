#include <stdbool.h>

#include "../src/JSONParser.h"

int main() {
    char  buffer[16][BUFFERSIZE];

    uint16_t length;
    settings_getString_Array("children/person1", *buffer, &length);

    return 0;
}
