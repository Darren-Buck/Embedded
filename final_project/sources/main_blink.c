#include <stdio.h>
#include <cjson/cJSON.h> // Include cJSON library header

#include "morse.h"

#define BUFSIZE 100

int main_blink(const cJSON *morse) {
    // Check if the morse object is a string and not NULL
    if (cJSON_IsString(morse) && (morse->valuestring != NULL)) {
        const char *text = morse->valuestring; // Extract text from morse object

        char morseOutput[BUFSIZE] = "";

    // Fill in the code for `translate_to_morse`
    translate_to_morse(text, morseOutput, BUFSIZE - 1);
    printf("Morse Code: %s\n", morseOutput);

    // Passe `morseOutput` to the morse_blink_led function
    // Update the morse_blink_led to blink accordingly
    morse_blink_led(morseOutput);

    return 0;
    }
}
