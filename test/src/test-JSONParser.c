#include <unity.h>
#include <stdbool.h>

#include <JSONParser.h>


void TEST_settings_getString(void) {
    char buffer[64];

    // NULL check
    int result = settings_getString("spouse", buffer);
    TEST_ASSERT_EQUAL(-1, result);

    settings_getString("firstName", buffer);
    TEST_ASSERT_EQUAL_STRING("John", buffer);

    settings_getString("lastName", buffer);
    TEST_ASSERT_EQUAL_STRING("Smith", buffer);

    settings_getString("address/streetAddress", buffer);
    TEST_ASSERT_EQUAL_STRING("21 2nd Street", buffer);

    settings_getString("address/postalCode", buffer);
    TEST_ASSERT_EQUAL_STRING("10021-3100", buffer);

    settings_getString("city", buffer);
    TEST_ASSERT_EQUAL_STRING("San fransico", buffer);
}

void TEST_settings_getInt(void) {
    int value;

    settings_getInt("age", &value);
    TEST_ASSERT_EQUAL(27, value);

    settings_getInt("address/state", &value);
    TEST_ASSERT_EQUAL(999, value);
}

void TEST_settings_getBool(void) {
    bool value = true;

    settings_getBool("isAlive", &value);
    TEST_ASSERT_FALSE(value);
}

void TEST_settings_getString_Array(void) {
    char buffer[16][BUFFERSIZE];
    int length;

    const char test1[][BUFFERSIZE] = {
        "Jack",
        "Doe"
    };
    settings_getString_Array("children/person1", *buffer, &length);
    TEST_ASSERT_EQUAL_STRING(test1[0], buffer[0]);
    TEST_ASSERT_EQUAL_STRING(test1[1], buffer[1]);

    const char test2[][BUFFERSIZE] = {
        "Piet",
        "Puck"
    };
    settings_getString_Array("children/person2", *buffer, &length);
    TEST_ASSERT_EQUAL_STRING(test2[0], buffer[0]);
    TEST_ASSERT_EQUAL_STRING(test2[1], buffer[1]);

    const char test3[][BUFFERSIZE] = {
        "home",
        "office"
    };
    settings_getString_Array("phoneNumbers/type", *buffer, &length);
    TEST_ASSERT_EQUAL_STRING(test3[0], buffer[0]);
    TEST_ASSERT_EQUAL_STRING(test3[1], buffer[1]);

    const char test4[][BUFFERSIZE] = {
        "212 555-1234",
        "646 555-4567"
    };
    settings_getString_Array("phoneNumbers/number", *buffer, &length);
    TEST_ASSERT_EQUAL_STRING(test4[0], buffer[0]);
    TEST_ASSERT_EQUAL_STRING(test4[1], buffer[1]);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    // Singles
    RUN_TEST(TEST_settings_getString);
    RUN_TEST(TEST_settings_getInt);
    RUN_TEST(TEST_settings_getBool);

    // Arrays
    RUN_TEST(TEST_settings_getString_Array);

    UNITY_END();

    return 0;
}