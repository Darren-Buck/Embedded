#include "ssd1306.h"
#include "bmp280_i2c.h"
#include <stdlib.h> 
#include <stdint.h>
#include "oled_txt.h"
#include <stdio.h>
#include <string.h>
#include "wiringx.h"

int main() {


// Mandatory Initialization
    wiringx_init();

    if(InitOLEDAddress() == -1)
    {
        printf("OLED initialization error, exiting program.");
        exit(-1);
    } 
    if(InitOLEDResolution() == -1)
    {
        printf("OLED resolution initialization error, exiting program.");
        exit(-1);
    }

    SettingParameters();
    ClearScreen();
    char barometerString[200];
    while (1) {
        struct bmp280_i2c result = read_temp_pressure();
        sprintf(barometerString,"Temperature: %.2fC\\nPressure: %.3fkPa", result.temperature, result.pressure);
        ssd1306_oled_write_string(0x00, barometerString);
        sleep(1);
        ClearScreen();
    }

    return 0;
}