#include "unity.h"
#include "delay.h"
#include "morse.h"

extern int mock_delay_called;
extern int mock_delay_duration;

// if needed
void setUp(void)
{
    // Set up any required structures or variables before each test
}

// if needed
void tearDown(void)
{
    // Clean up after each test
}

// Test function for normal alphabetic input
void test_AlphabeticInput(void)
{
    char output[100];
    translate_to_morse("hello", output, 99);

    // hello
    char *expected = ".... . .-.. .-.. ---";

    TEST_ASSERT_EQUAL_STRING(expected, output);
}

// Test function for numeric input
void test_NumericInput(void)
{
    char output[100];
    // Add test code for numeric input such as "123"
    translate_to_morse("123", output, 99);

    // 123
    char *expected = ".---- ..--- ...--";

    TEST_ASSERT_EQUAL_STRING(expected, output);
}

// Test function for mixed alphanumeric input
void test_MixedAlphanumericInput(void)
{
    char output[100];
    // Add test code for numeric input such as "abc123"
    translate_to_morse("abc123", output, 99);

    // abc123
    char *expected = ".- -... -.-. .---- ..--- ...--";

    TEST_ASSERT_EQUAL_STRING(expected, output);
}

// Test function for mixed case input
void test_MixedCaseAlphanumericInput(void)
{
    char output[100];
    // Add test code for numeric input such as "AbC123"
    translate_to_morse("AbC123", output, 99);

    // AbC123
    char *expected = ".- -... -.-. .---- ..--- ...--";

    TEST_ASSERT_EQUAL_STRING(expected, output);
}

// Test function for words with spaces
void test_CanHandleSpaces(void)
{
    char output[100];
    // Add test code for numeric input such as "AbC123"
    translate_to_morse("Hello World", output, 99);

    // Hello World
    char *expected = ".... . .-.. .-.. --- / .-- --- .-. .-.. -..";

    TEST_ASSERT_EQUAL_STRING(expected, output);
}

// Test function for non-representable binary data
void test_NonRepresentableBinaryData(void)
{
    // Nothing to do here, just showing example
    char output[100];
    char binaryData[] = {0x00, 0xFF, 0x55, 0x7F}; // Example binary data
    translate_to_morse(binaryData, output, 99);
    // Since Morse code is not defined for arbitrary binary data, we need to define expected behavior.
    // For example, if non-representable characters are translated as empty strings:
    TEST_ASSERT_EQUAL_STRING("", output);
}

#if !defined(RELEASE) && !defined(DEBUG)
// Test that we can blink an LED
void test_MorseTiming(void)
{
    // Initialize mock function variables
    mock_initialize();

    // Translate "SOS" to Morse code
    char output[150];
    translate_to_morse("SOS", output, sizeof(output) - 1);

    // Blink LED according to Morse code
    morse_blink_led(output);

    // printf("mock_delay_called: %d\n", mock_delay_called);
    // printf("mock_delay_duration: %d\n", mock_delay_duration);

    // Expected values
    int expected_delay_calls = 17;
    int expected_delay_duration = 27;

    // Assert the number of delay calls
    TEST_ASSERT_EQUAL(expected_delay_calls, mock_delay_called);

    // Assert the total duration of delays
    TEST_ASSERT_EQUAL(expected_delay_duration, mock_delay_duration);
}
#endif

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_AlphabeticInput);
    RUN_TEST(test_NumericInput);
    RUN_TEST(test_MixedAlphanumericInput);
    RUN_TEST(test_CanHandleSpaces);
    RUN_TEST(test_MixedCaseAlphanumericInput);
    RUN_TEST(test_NonRepresentableBinaryData);

#if !defined(RELEASE) && !defined(DEBUG)
    RUN_TEST(test_MorseTiming);
#endif

    return UNITY_END();
}
