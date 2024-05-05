#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <cjson/cJSON.h>

void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    if (message->payloadlen)
    {
        printf("%s %s\n", message->topic, (char *)message->payload);
        cJSON *root = cJSON_Parse(message->payload);
        if (root)
        {
            // const cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
            // if (cJSON_IsString(name) && (name->valuestring != NULL))
            // {
            //     printf("Name: %s\n", name->valuestring);
            // }

            // const cJSON *number = cJSON_GetObjectItemCaseSensitive(root, "number");
            // if (cJSON_IsNumber(number))
            // {
            //     printf("Number: %d\n", number->valueint);
            // }

            // The above are examples of ways strings and numbers can be sent
            // via mqtt. You'll need to add support here for additional tasking.

            // Add an object named "task". (similar to name)
            // You'll need to use strncmp or strcmp to check if the valuestring
            // is "get_temperature" or "get_pressure" or "get_temperature_pressure"
            // Based on that value, you will use your bmp280 library function
            // to get the temperature, pressure or both.
            // Use your ssd1306 library to write the value(s) to the OLED.
            const cJSON *task = cJSON_GetObjectItemCaseSensitive(root, "task");
            if (cJSON_IsString(task) && (task->valuestring != NULL))
            {
                if (strcmp(task->valuestring, "get_temperature") == 0)
                {
                    // Handle temperature task
                    float temperature = bmp280_get_temperature();
                    char temperature_string[20];
                    snprintf(temperature_string, sizeof(temperature_string), "%.2f C", temperature);
                    ssd1306_oled_write_string(0, "Temperature:");
                    ssd1306_oled_set_XY(0, 2);
                    ssd1306_oled_write_string(0, temperature_string);
                }
                else if (strcmp(task->valuestring, "get_pressure") == 0)
                {
                    // Handle pressure task
                    float pressure = bmp280_get_pressure();
                    char pressure_string[20];
                    snprintf(pressure_string, sizeof(pressure_string), "%.2f Pa", pressure);
                    ssd1306_oled_write_string(0, "Pressure:");
                    ssd1306_oled_set_XY(0, 2);
                    ssd1306_oled_write_string(0, pressure_string);
                }
                else if (strcmp(task->valuestring, "get_temperature_pressure") == 0)
                {
                    // Handle temperature and pressure task
                    float temperature = bmp280_get_temperature();
                    float pressure = bmp280_get_pressure();
                    char temperature_string[20];
                    char pressure_string[20];
                    snprintf(temperature_string, sizeof(temperature_string), "Temp: %.2f C", temperature);
                    snprintf(pressure_string, sizeof(pressure_string), "Press: %.2f Pa", pressure);
                    ssd1306_oled_write_string(0, "Temperature:");
                    ssd1306_oled_set_XY(0, 2);
                    ssd1306_oled_write_string(0, temperature_string);
                    ssd1306_oled_set_XY(0, 4);
                    ssd1306_oled_write_string(0, "Pressure:");
                    ssd1306_oled_set_XY(0, 6);
                    ssd1306_oled_write_string(0, pressure_string);
                }
                // Add more task handling as needed
            }


            // Add an object named "string_msg". (similiar to name)
            // This is simply a message that can be printed onto the OLED.
            const cJSON *string_msg = cJSON_GetObjectItemCaseSensitive(root, "string_msg");
            if (cJSON_IsString(string_msg) && (string_msg->valuestring != NULL))
            {
                // Handle string message
                ssd1306_oled_write_string(0, string_msg->valuestring);
            }


            // Add an object named "int_msg". (similiar to number)
            // This is simply a message that can be printed onto the OLED.
            const cJSON *int_msg = cJSON_GetObjectItemCaseSensitive(root, "int_msg");
            if (cJSON_IsNumber(int_msg))
            {
                // Handle integer message
                char int_msg_string[20];
                snprintf(int_msg_string, sizeof(int_msg_string), "%d", int_msg->valueint);
                ssd1306_oled_write_string(0, int_msg_string);
            }


            // Bonus: Add a case for "morse". This will use your morse code project
            // to blink the led in morse code.
            const cJSON *morse = cJSON_GetObjectItemCaseSensitive(root, "morse");
            if (cJSON_IsString(morse) && (morse->valuestring != NULL))
            {
                // Handle morse code
                morse_code_blink(morse->valuestring);
            }


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
    wiringx_init();

    ssd1306_init(0);
    ssd1306_oled_default_config(64, 128);


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

    printf("Press Enter to quit...\n");
    getchar();

    // Cleanup
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}


// Initialize ssd1306 library (do this once in main) 
// The 0 here relates to the i2c bus you're using, use another number if needed ssd1306_init(0);
// This sets the screen (do this once in main) ssd1306_oled_default_config(64, 128);
 // These should be done before any printing ssd1306_oled_clear_screen(); ssd1306_oled_set_XY(0, 0); 
 // setup a buffer for writing char msg[250] = {0};
 // example using the temp sensor struct bmp280_i2c tmp = read_temp_pressure(); sprintf(msg, "Temp: %f", tmp.temperature);
 // writing to the string (0 is the font size, keep it at 0) ssd1306_oled_write_string(0, msg);