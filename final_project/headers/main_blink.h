#ifndef MAIN_BLINK_H
#define MAIN_BLINK_H

#include <cjson/cJSON.h> // Include cJSON library header

/**
 * @brief Translates the given text to Morse code and blinks LED accordingly.
 * 
 * @param text_object Pointer to cJSON object containing the text to be translated.
 * @return int 0 if successful, -1 if there's an error.
 */
int main_blink(const cJSON *text_object);

#endif /* MAIN_BLINK_H */
