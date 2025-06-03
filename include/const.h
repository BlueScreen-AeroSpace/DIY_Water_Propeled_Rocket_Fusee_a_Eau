#pragma once

#define SERIAL_SPEED 115200

#define EMPTY ""
#define DEFAULT_ZERO 0
#define INTERVAL_90 90000 // 90 secondes
#define INTERVAL_15 15000 // 15 secondes
#define INTERVAL_5 5000   // 5 secondes
#define INTERVAL_4 4000
#define INTERVAL_3 3000
#define INTERVAL_2 2000
#define INTERVAL_1 1000
#define INTERVAL_500 500 // 500 millisecondes
#define INTERVAL_400 400
#define INTERVAL_300 300
#define INTERVAL_200 200
#define INTERVAL_100 100
#define INTERVAL_75 75
#define INTERVAL_50 50 // 50 millisecondes
#define INTERVAL_40 40
#define INTERVAL_30 30
#define INTERVAL_20 20
#define INTERVAL_10 10
#define TO_SEC 1000.0f

// JSONManager
#define JSON_FILE_PATH "/config.json"
#define JSON_ERROR "error"

// BMP280
#define SDA_PIN 21
#define SCL_PIN 22
#define BME_ADD 0x76 // SD0 sur GND. Si VCC: 0x77    hey ben si j'utilise Wire.begin() pas besoin de pluger le SDO sur GND ou VCC ADD par défaut 0x76
#define SEALEVELPRESSURE_HPA (1013.25)
#define DEGREE "°c"
#define METER "m"
#define KPA "kPa"
#define PERCENT "%"
#define KILOPASCAL 1000.0
#define MS "m/s" // Accélération en mètre par seconde au carré. La gravité est une accélération constante de 9.81m/s² soit 1G.

// ADXL345
#define ADXL_ADD 0x53
#define G_CONST 9.81f // Constante De la gravité.

// WIFI D1 Mini Data loggar shield
#define SD_CS 5    // D8    mauve  CS
#define SD_SCK 18  // D5    gris   clock (SCK)
#define SD_MISO 23 // D7    jaune  DI
#define SD_MOSI 19 // D6    orange DO
#define CSV ".csv"
#define DEFAULT_FILENAME "DEFAULT.csv"

// servo motor
#define SERVO_PIN 26
#define START_POS 90
#define ROTATE_90 180

// ChuteManager , marge d'erreur de 2 metre ou 2 metres seconde pour l'altitude et la vitesse
#define MARGIN_ERROR 1.5f

// LED
#define PIN_LED 25

// DELPanelManager

#define LED_PIN_PANEL 17
#define LED_COUNT_PANEL 256
#define MATRIX_WIDTH_PANEL 16
#define MATRIX_HEIGHT_PANEL 16

// OLED Display

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3c

// Data logger
#define MAX_DATA_RECORD_TIME 120000