#pragma once

#define SERIAL_SPEED 115200

#define EMPTY ""
#define DEFAULT_ZERO 0
#define INTERVAL_5 5000                 // 5 secondes
#define INTERVAL_4 4000
#define INTERVAL_3 3000
#define INTERVAL_2 2000
#define INTERVAL_1 1000
#define INTERVAL_500 500                // 500 millisecondes
#define INTERVAL_400 400
#define INTERVAL_300 300
#define INTERVAL_200 200
#define INTERVAL_100 100
#define INTERVAL_50 50                  // 50 millisecondes
#define INTERVAL_40 40
#define INTERVAL_30 30
#define INTERVAL_20 20
#define INTERVAL_10 10
#define TO_SEC 1000.0

// JSONManager
#define JSON_FILE_PATH "/config.json"
#define JSON_ERROR "error"

// BMP280
#define SDA_PIN 21
#define SCL_PIN 22
#define BMP_ADD 0x76                    // SD0 sur GND. Si VCC: 0x77    hey ben si j'utilise Wire.begin() pas besoin de pluger le SDO sur GND ou VCC ADD par défaut 0x76
#define SEALEVELPRESSURE_HPA (1013.25)
#define DEGREE "°c"
#define METER "m"
#define KPA "kPa"
#define PERCENT "%" 
#define KILOPASCAL 1000.0
#define MS "m/s"                      // Accélération en mètre par seconde au carré. La gravité est une accélération constante de 9.81m/s² soit 1G.

// ADXL345
#define ADXL_ADD 0x53                   
#define G_CONST 9.81f                   // Constante De la gravité.

// WIFI D1 Mini Data loggar shield
#define SD_CS 5         //D8    mauve  CS                                    
#define SD_SCK 18       //D5    gris   clock (SCK)
#define SD_MISO 23      //D7    jaune  DI
#define SD_MOSI 19      //D6    orange DO
#define CSV ".csv"
#define CSV_TELEMETRY_HEADER "time;temperature;altitude;pressure;speed;axeZg;axeYg;axeXg"   // Temporaire pour essait, à redéfinir   

// servo motor
#define SERVO_PIN 25
#define START_POS 0
#define ROTATE_90 80

// ChuteManager , marge d'erreur de 2 metre ou 2 metres seconde pour l'altitude et la vitesse
#define MARGIN_ERROR 1.25

// SensorDiscovery 
// 
#define TEMP_DISCOVERY_TOPIC "homeassistant/sensor/bmp280_temperature/config"
#define PRESSURE_DISCOVERY_TOPIC "homeassistant/sensor/bmp280_pressure/config"
#define SPEED_DISCOVERY_TOPIC "homeassistant/sensor/esp32_speed/config"

#define TEMP_TOPIC "homeassistant/sensor/bmp280/temperature"
#define PRESSURE_TOPIC "homeassistant/sensor/bmp280/pression"
#define ALTITUDE_TOPIC "homeassistant/sensor/bmp280/altitude"
#define AXEX_TOPIC "homeassistant/sensor/adxl345/x"
#define AXEY_TOPIC "homeassistant/sensor/adxl345/y"
#define AXEZ_TOPIC "homeassistant/sensor/adxl345/z"
#define SPEED_TOPIC "homeassistant/sensor/esp32_speed"

#define SWITCH_TOPIC "homeassistant/switch/launch/set"
#define SWITCH_CONFIRMATION_TOPIC "homeassistant/status/rocket"

//MQTT_Service

//  SERVER_IP "10.30.204.140" // Valeurs actuelles pour le mqtt broker
//  SERVER_PORT 1883
//  USER "jennifernino"
//  PASS "willino.com"      

// LED
#define PIN_LED 26