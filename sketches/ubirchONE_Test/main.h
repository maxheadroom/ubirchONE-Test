
// config.h contains sensitive information, like the
// cell phone APN, username and password
#include "config.h"

#define PRINT(s) Serial.print(F(s))
#define PRINTLN(s) Serial.println(F(s))
#define DEBUG(s) Serial.print(s)
#define DEBUGLN(s) Serial.println(s)


#define UBIRCH_NO1_PIN_LED      13
#define UBIRCH_NO1_PIN_WATCHDOG 6

// == special ubirch #1 stuff ==
#define enable_led()    digitalWrite(UBIRCH_NO1_PIN_LED, HIGH)
#define disable_led()   digitalWrite(UBIRCH_NO1_PIN_LED, LOW)

#define enable_watchdog()   pinMode(UBIRCH_NO1_PIN_WATCHDOG, INPUT)
#define disable_watchdog()  pinMode(UBIRCH_NO1_PIN_WATCHDOG, OUTPUT)


// the server url for up and download (BASE)
const char SERVER_URL[] PROGMEM = "http://jira.explain-it.org/temp/iot.html?imei=";