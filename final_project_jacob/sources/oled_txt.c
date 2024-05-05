#include <stdlib.h> 
#include <stdint.h>
#include "ssd1306.h"
#include <stdio.h>


void ClearScreen(){
    int returnCode = 0;
    returnCode = ssd1306_oled_clear_screen();
    if(returnCode){
        printf("Clear screen error, exiting program.");
    }
}


int InitOLEDAddress() {
    int flag = 0; 
    int returnCode = 0; 
    uint8_t i2cAddress = 0; 
    int address = 0;

    while (!flag) { 
        printf("Select I2C Address:\n");
        printf(" 1. Address 0 (0x00)\n");
        printf(" 2. Address 2 (0x02)\n");
        printf(" 3. Address 3 (0x03)\n");
        printf("Option: ");  
        fflush(stdout);
        scanf("%d", &address);  

        switch (address) {
        case 1:
            i2cAddress  = 0x00; 
            break;
        case 2:
            i2cAddress  = 0x02;
            break;
        case 3:
            i2cAddress  = 0x03;
            break;
        default:
            printf("Invalid option. Please choose a valid option.\n");
            continue; 
        }

        returnCode = ssd1306_init(i2cAddress ); // Initialize the OLED with the chosen I2C address

        if (returnCode!= 0) {
            printf("No OLED attached to /dev/i2c-%d\n", i2cAddress );
        } else {
            printf("Initialization successful on /dev/i2c-%d\n\n", i2cAddress );
            flag = 1; 
        }
    }
    return 0; 
}


int InitOLEDResolution()
{
    int flag = 0;
    int resolution = 0;
    uint8_t resolution_rows = 0;
    uint8_t resolution_columns = 0;
    int returnCode = 0;

    while(!flag){
        printf("Please select the numerical option for the desired screen resolution:\n");
        printf(" 1. 128x64\n");
        printf(" 2. 128x32\n");
        printf(" 3. 64x48\n");
        printf("Option: ");
        fflush(stdout);
        scanf("%d",&resolution);
        switch (resolution)
        {
        case(1):
            resolution_rows = 64;
            resolution_columns = 128;
            break;
        case(2):
            resolution_rows = 32;
            resolution_columns = 128;
        break;
        case(3):
            resolution_rows = 48;
            resolution_columns = 64;
        break;
        default:
            printf("Invalid option. Please choose a valid option.\n");
            continue; 
        }

        returnCode = ssd1306_oled_default_config(resolution_rows, resolution_columns);
        if(returnCode != 0)
        {
            printf("Resolution error.");
            return -1;
        }
        else{
            printf("Resolution Initialized\n\n");
            flag = 1;
        }
    }
    return 0 ;
}


int InitFontSize(){
    // font_small = 0x00;
    // font_normal = 0x01;
    uint8_t font = 0x01;
    int userInput = 0;
    int returnCode = 0;
    int flag = 0;
    int confirm = 0;
    char testMessage[13] = "I Love Tacos";
    
    while(!flag){
        printf("Please select the numerical font size option:\n 1. Small\n 2. Normal\n");
        printf("Option: ");
        fflush(stdout);
        scanf("%d", &userInput); 

        switch (userInput) {
            case 1:
                printf("Font selected: Small\n");
                font = 0x00;
                break;
            case 2:
                printf("Font selected: Normal\n");
                break;
            default:
                printf("Invalid selection. Defaulting to normal font.\n");
                break;
        }

        returnCode = ssd1306_oled_write_string(font,testMessage);
         if (returnCode) {
                    printf("Error setting default font.\n");
                    return -1;
         }

        printf("Happy with your choice? Please select a numerical option:\n 1. Yes\n 2. No\n");
        printf("Option: ");
        fflush(stdout);
        scanf("%d", &confirm);
        switch (confirm)
        {
        case(1):
            flag = 1;
            break;
        default:
            printf("Let's try again...\n");
            ClearScreen();
            continue;
        }
    }
    return 0;
}

int SettingParameters(){
    int userInput = 0;
    int flag = 0;

    while(!flag){
        printf("Setting Device Parameters\n");
        printf("  1. Clear Line\n");
        printf("  2. Clear Screen\n");
        printf("  3. Display State\n");
        printf("  4. Font Size\n");
        printf("  5. Inverted Display\n");
        printf("  6. Line Text\n");
        printf("  7. Print Message\n");
        printf("  8. Rotate Screen\n");
        printf("  9. Set text cursor start point\n");
        printf("  10. Help\n");
        printf("  11. Skip\n\n");
        printf("Please select one of the numerical options\n");
        printf("Options: ");
        fflush(stdout);
        scanf("%d",&userInput);

        switch (userInput) {
        case 1:
            // Case 1 code
            break;
        case 2:
            ClearScreen();
            break;
        case 3:
            // Case 3 code
            break;
        case 4:
            if(InitFontSize() == -1){
                exit(-1);
            } 
            break;
        case 5:
            // Case 5 code
            break;
        case 6:
            // Case 6 code
            break;
        case 7:
            // Case 7 code
            break;
        case 8:
            // Case 8 code
            break;
        case 9:
            // Case 9 code
            break;
        case 10:
            // Case 10 code
            break;
        case 11:
            break;
        default:
            printf("Invlaid selection try again.");
            userInput = 0;
            continue;
        }
        printf("Are you happy with your choices? Please choose from the numerical options.\n  1. Yes\n  2. No\n\n");
        printf("Option: ");
        fflush(stdout);
        scanf("%d",&userInput);
        switch (userInput)
        {
        case 1:
            printf("Set-up complete.\n\n");
            flag = 1;
            break;
        case 2:
                printf("Running it back.!\n\n");
                continue;
                break;
        
        default:
            printf("Invalid option!\n\n");
            continue;
        }
    }
    
}
