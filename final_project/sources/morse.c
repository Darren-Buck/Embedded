#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "morse.h"
#include "delay.h"
#include "blink.h"

const char *char_to_morse(char c)
{
    // Define Morse code for each alphabet and digit
    static const char *morseCode[36] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                                        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                                        "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
                                        "...--", "....-", ".....", "-....", "--...", "---..", "----."};

    if (c >= 'a' && c <= 'z')
    {
        return morseCode[c - 'a'];
    }
    else if (c >= '0' && c <= '9')
    {
        return morseCode[c - '0' + 26];
    }
    else
    {
        return ""; // Return empty string for other characters
    }
}

// Function to convert a word to Morse code
// Use the delimiter / for any spaces between words
void translate_to_morse(const char *text, char *morseOutput, int morseOutputSize)
{
    // Loop through the text to convert each
    // charactor to morse code.
    // char_to_morse function is provided above but may not
    // handle all cases.

    int len = strlen(text);
    memset(morseOutput, 0, morseOutputSize);

    for (int i = 0; i < len; i++) {
        // Check for space to insert a word delimiter
        if (text[i] == ' ') {
            strncat(morseOutput, " / ", morseOutputSize - strlen(morseOutput) - 1);
            continue;
        }

        const char *morseChar = char_to_morse(tolower((unsigned char)text[i])); // Convert character to lower and then to Morse
        strncat(morseOutput, morseChar, morseOutputSize - strlen(morseOutput) - 1);

        // Add a space after each Morse character unless it's the last one or before a space
        if (i < len - 1 && text[i + 1] != ' ') {
            strncat(morseOutput, " ", morseOutputSize - strlen(morseOutput) - 1);
        }
    }
}

void morse_blink_led(const char *morseCode)
{
    INIT_LED();
    // Blink LED based on the timing needed
    // 1 Unit = 1 Second

    // Use LED_HIGH() to turn on led
    // Use LED_LOW() to turn off led
    LED_HIGH();
    LED_LOW();

    // int duration = 1 or w/e value you need
    // Use DELAY(duration) to sleep the appropriate units
    // Rmemeber 1 unit = 1 second for this assignment



    int len = strlen(morseCode);
    for (int i = 0; i < len; i++)
    {
        if(morseCode[i] == '.') {
            LED_HIGH();
            DELAY(1); // Dot duration
            LED_LOW();
            printf("%c\n",morseCode[i]);

        }
        else if(morseCode[i] == '-') {
            LED_HIGH();
            DELAY(3); // Dash duration
            LED_LOW();
            printf("%c\n",morseCode[i]);
        }

        // If the current character is not the last one
        if (i < len - 1) {
            // If next character is a space or slash, it's either end of a letter or word
            if(morseCode[i + 1] == ' ') {
                if(morseCode[i + 2] == '/') {
                    DELAY(7); // Space between words
                    i += 2; // Skip the next space and slash
                } else {
                    DELAY(3); // Space between letters
                    i++; // Skip the next space
                }
            }
            // If the current character is a dot or a dash and the next character is not a space, 
            // it's part of the same letter
            else if(morseCode[i] == '.' || morseCode[i] == '-') {
                DELAY(1); // Space between parts of the same letter
            }
        }
    }
}
