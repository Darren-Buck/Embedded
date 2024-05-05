#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <cjson/cJSON.h>
#include "wiringx.h"
#include "oled_txt.h"
#include "ssd1306.h"
#include "bmp280_i2c.h"
#include <stdint.h>
#include <string.h>
#include <unistd.h>

void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    char numberMessageToOLED[250] = {0};
    char barometerString[200];
    ClearScreen();
    ssd1306_oled_set_XY(0, 0);
    printf("About to recieve a callback\n");

    if (message->payloadlen)
    {
        printf("%s %s\n", message->topic, (char *)message->payload);
        cJSON *root = cJSON_Parse(message->payload);
        if (root)
        {
        const cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
        if (cJSON_IsString(name) && (name->valuestring != NULL))
        {
        printf("Name: %s\n", name->valuestring);
        sleep(5);
        ClearScreen();
        ssd1306_oled_set_XY(0, 0);
        }

        const cJSON *number = cJSON_GetObjectItemCaseSensitive(root, "number");
        if (cJSON_IsNumber(number))
        {
        printf("Number: %d\n", number->valueint);
        sleep(5);
        ClearScreen();
        ssd1306_oled_set_XY(0, 0);
        }
        printf("%s %s\n", message->topic, (char *)message->payload);
        cJSON *root = cJSON_Parse(message->payload);
        const cJSON *task = cJSON_GetObjectItemCaseSensitive(root, "task");
        if (cJSON_IsString(task) && (task->valuestring != NULL)){
                struct bmp280_i2c result = read_temp_pressure();
                if(strcmp(task->valuestring, "get_temperature") == 0){
                        sprintf(barometerString,"Temperature: %.2fC",result.temperature);
                        ssd1306_oled_write_string(0x00, barometerString);
                        sleep(5);
                        ClearScreen();
                        ssd1306_oled_set_XY(0, 0);
                }
                else if(strcmp(task->valuestring, "get_pressure") == 0){
                    sprintf(barometerString,"Pressure: %.3fkPa",result.pressure);
                    ssd1306_oled_write_string(0x00, barometerString);
                    sleep(5);
                    ClearScreen();
                    ssd1306_oled_set_XY(0, 0);
                }
                else if(strcmp(task->valuestring, "get_temperature_pressure") == 0){
                    sprintf(barometerString,"Temperature: %.2fC\\nPressure: %.3fkPa", result.temperature, result.pressure);
                    ssd1306_oled_write_string(0x00, barometerString);
                    sleep(5);
                    ClearScreen();
                    ssd1306_oled_set_XY(0, 0);
                }
            }
        // Add an object named "string_msg". (similiar to name)
        // This is simply a message that can be printed onto the OLED.
        const cJSON *string_msg = cJSON_GetObjectItemCaseSensitive(root, "string_msg");
        if (cJSON_IsString(string_msg) && (string_msg->valuestring != NULL)){
            ssd1306_oled_write_string(0x00, string_msg->valuestring);
            sleep(5);
            ClearScreen();
            ssd1306_oled_set_XY(0, 0);
        }
        // Add an object named "int_msg". (similiar to number)
        // This is simply a message that can be printed onto the OLED.
        const cJSON *int_msg = cJSON_GetObjectItemCaseSensitive(root, "int_msg");
        if (cJSON_IsNumber(int_msg)){
            sprintf(numberMessageToOLED,"The number is %d\n",int_msg->valueint);
            ssd1306_oled_write_string(0x00, numberMessageToOLED );
            sleep(5);
            ClearScreen();
            ssd1306_oled_set_XY(0, 0);
        }
        // Bonus: Add a case for "morse". This will use your morse code project
        // to blink the led in morse code.
        cJSON_Delete(root);
        }
        else
        {
            printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        }
    }
    else
    {
        printf("%s (null)\n", message->topic);
    }
}

int main(int argc, char *argv[])
{
    struct mosquitto *mosq;

    // Initialize the Mosquitto library
    mosquitto_lib_init();

    // Create a new Mosquitto runtime instance with a random client ID
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq)
    {
        fprintf(stderr, "Could not create Mosquitto instance\n");
        exit(-1);
    }

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

        // Assign the message callback
    mosquitto_message_callback_set(mosq, message_callback);

    // Connect to an MQTT broker
    if (mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Could not connect to broker\n");
        exit(-1);
    }

    // Subscribe to the topic
    mosquitto_subscribe(mosq, NULL, "test/topic", 0);

    // Start the loop
    mosquitto_loop_start(mosq);

    // printf("Press Enter to quit...\n");
    // getchar();

    while(1)
    {
    
    }

    // Cleanup
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    printf("Exiting the skeeter\n");
    return 0;
}
