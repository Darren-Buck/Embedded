#include "delay.h"

// Nothing to do here
// This allows our test code to use our DELAY macro
// As long as we're not in release mode

#if !defined(RELEASE) && !defined(DEBUG)
// Global variables to track mock function calls and durations
int mock_delay_called = 0;
int mock_delay_duration = 0;

void mock_initialize()
{
    mock_delay_called = 0;
    mock_delay_duration = 0;
}

// Mock function for delay to simulate LED blink
void mock_delay(int duration)
{
    mock_delay_called++;
    mock_delay_duration += duration;
}

#endif