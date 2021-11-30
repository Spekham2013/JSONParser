#include <unity.h>
#include <stdbool.h>

#include <JSONParser.h>


void TEST_settings_getString(void) {
    char buffer[64];

    // NULL check
    settings_getString("spouse", buffer);
    TEST_ASSERT_NULL(buffer);

    settings_getString("firstName", buffer);
    TEST_ASSERT_EQUAL_STRING("John", buffer);

    settings_getString("lastName", buffer);
    TEST_ASSERT_EQUAL_STRING("Smith", buffer);

    settings_getString("address/streetAddress", buffer);
    TEST_ASSERT_EQUAL_STRING("21 2nd Street", buffer);

    settings_getString("address/postalCode", buffer);
    TEST_ASSERT_EQUAL_STRING("John", buffer);

    settings_getString("city", buffer);
    TEST_ASSERT_EQUAL_STRING("San fransico", buffer);
}

void TEST_settings_getInt(void) {
    int value;

    settings_getInt("age", &value);
    TEST_ASSERT_EQUAL(27, value);

    settings_getInt("state", &value);
    TEST_ASSERT_EQUAL(999, value);
}

void TEST_settings_getBool(void) {
    bool value = true;

    settings_getBool("isAlive", &value);
    TEST_ASSERT_FALSE(value);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    // RUN_TEST(TEST_settings_getString);
    // RUN_TEST(TEST_settings_getInt);
    RUN_TEST(TEST_settings_getBool);

    UNITY_END();

    return 0;
}