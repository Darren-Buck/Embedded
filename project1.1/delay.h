#ifndef DELAY_H
#define DELAY_H

#include <unistd.h>

#if !defined(RELEASE) && !defined(DEBUG)

void mock_initialize();
void mock_delay(int duration);
#define DELAY(duration) mock_delay(duration)

#else
// If we define RELEASE or DEBUG our delay is sleep
#define DELAY(duration) sleep(duration)
#endif

#endif // DELAY_H