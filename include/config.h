#pragma once
#include <Arduino.h>
// #include <WiFiManager.h>

#define PORTAL_SSID "5gtP3pp3rConfigurationESP32"           // hot spot cell pour wifi extérieur
#define PORTAL_PASSWWORD "Pouet&666"                        // hot spot cell pour wifi extérieur
#define TIMEOUT 180

#define NB_TRY_MAX 15      

#define HASS_USER_PARAM_1 "HASS_USER"   // id du champ
#define HASS_USER_PARAM_2 "HASS USER"   // nom du champ
#define HASS_USER_PARAM_3 "defaut"      // valeur par défaut du champ
#define HASS_USER_PARAM_4 40            // longeur max champ

#define HASS_PASS_PARAM_1 "HASS_PASS"
#define HASS_PASS_PARAM_2 "HASS PASS"
#define HASS_PASS_PARAM_3 "defaut"
#define HASS_PASS_PARAM_4 40

#define HASS_IP_PARAM_1 "HASS_IP"
#define HASS_IP_PARAM_2 "HASS IP"
#define HASS_IP_PARAM_3 "defaut"
#define HASS_IP_PARAM_4 40

#define HASS_PORT_PARAM_1 "HASS_PORT"
#define HASS_PORT_PARAM_2 "HASS PORT"
#define HASS_PORT_PARAM_3 "defaut"
#define HASS_PORT_PARAM_4 40





///                  nomchamp
//          __________________________
//         |   valeur par defaut       |
//         -----------------------------