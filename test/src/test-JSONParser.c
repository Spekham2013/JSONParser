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
    uint16_t length;

    const char test1[][BUFFERSIZE] = {
        "Jack",
        "Doe"
    };
    settings_getString_Array("address/person1", *buffer, &length);
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
void TEST_settings_getInt_Array(void) {
    int value[64];
    uint16_t elements;

    const int test1[] = {
        123456,
        65432
    };
    settings_getInt_Array("phoneNumbers/DIGIID", value, &elements);
    TEST_ASSERT_EQUAL(test1[0], value[0]);
    TEST_ASSERT_EQUAL(test1[1], value[1]);

    const int test2[] = {
        12,
        15,
        18
    };
    settings_getInt_Array("ChildrenAge", value, &elements);
    TEST_ASSERT_EQUAL(test2[0], value[0]);
    TEST_ASSERT_EQUAL(test2[1], value[1]);
    TEST_ASSERT_EQUAL(test2[2], value[2]);
}

void TEST_settings_getBool_Array(void) {
    bool value[64];
    uint16_t elements;

    settings_getBool_Array("Geslacht", value, &elements);
    TEST_ASSERT_TRUE (value[0]);
    TEST_ASSERT_FALSE(value[1]);
    TEST_ASSERT_TRUE (value[2]);

    settings_getBool_Array("phoneNumbers/State", value, &elements);
    TEST_ASSERT_TRUE (value[0]);
    TEST_ASSERT_FALSE(value[1]);
}

int main(int argc, char **argv) {
    settings_configureFilePath("/home/stephan/Documents/Synced/Projects/JSONParser/test/example.json");

    UNITY_BEGIN();

    // Singles
    RUN_TEST(TEST_settings_getString);
    RUN_TEST(TEST_settings_getInt);
    RUN_TEST(TEST_settings_getBool);

    // Arrays
    RUN_TEST(TEST_settings_getString_Array);
    RUN_TEST(TEST_settings_getInt_Array);
    RUN_TEST(TEST_settings_getBool_Array);

    UNITY_END();

    return 0;
}