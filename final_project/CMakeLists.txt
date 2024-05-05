cmake_minimum_required(VERSION 3.10)
project(final_project VERSION 1.0)

include_directories(sources headers)

# Source files here
set(SRCS sources/blink.c sources/bmp280_i2c.c sources/delay.c sources/linux_i2c.c sources/morse.c sources/ssd1306.c )

add_library(ssd1306 STATIC sources/ssd1306.c sources/linux_i2c.c)


add_library(bmp280 STATIC sources/bmp280_i2c.c)


add_library(blink STATIC sources/blink.c sources/morse.c sources/delay.c sources/main_blink.c)


# Find cJSON library
find_library(CJSON_LIB
  NAMES cjson
  PATHS "/app/install_cv1800b_cjson/lib"
  NO_DEFAULT_PATH
)

# Find Mosquitto library
find_library(MQTT_LIB
  NAMES mosquitto
  PATHS "/app/install_cv1800b_mqtt/lib"
  NO_DEFAULT_PATH
)

# Find SSL library
find_library(OPEN_SSL_LIB
  NAMES ssl
  PATHS "/app/install_cv1800b_openssl/lib"
  NO_DEFAULT_PATH
)

# Find CRYPTO library
find_library(CRYPTO_LIB
  NAMES crypto
  PATHS "/app/install_cv1800b_openssl/lib"
  NO_DEFAULT_PATH
)

# Check if all libraries were found
if(NOT CJSON_LIB OR NOT MQTT_LIB OR NOT OPEN_SSL_LIB OR NOT CRYPTO_LIB)
  message(FATAL_ERROR "One or more libraries (cJSON, Mosquitto, SSL) not found")
endif()


# Add executables
add_executable(subscriber subscriber.c ${SRCS})
add_executable(publisher publisher.c)


# Link libraries
target_link_libraries(subscriber ${CJSON_LIB} ${MQTT_LIB} ${OPEN_SSL_LIB} ${CRYPTO_LIB} blink bmp280 ssd1306)
target_link_libraries(publisher ${CJSON_LIB} ${MQTT_LIB} ${OPEN_SSL_LIB} ${CRYPTO_LIB})
