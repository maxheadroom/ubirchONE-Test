/**
 * ubirchONE-Test
 *
 * ...
 *
 * @author Falko Zurell
 *
 * == LICENSE ==
 * Copyright 2015 ubirch GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
  */

/* #include <MinimumSerial.h> */
#include <UbirchSIM800.h>
#include <SdFat.h>
#include "main.h"
extern "C" {
    #include "i2c/i2c.h"
}



UbirchSIM800 sim800 = UbirchSIM800();
#ifndef BAUD
#   define BAUD 9600
#endif

void setup() {
    pinMode(UBIRCH_NO1_PIN_LED, OUTPUT);
    pinMode(UBIRCH_NO1_PIN_WATCHDOG, OUTPUT);
    enable_led();

    enable_watchdog();

    Serial.begin(BAUD);

    if (!sim800.wakeup()) {
        Serial.println("SIM800 wakeup error");
// halt(3);
    }
    sim800.setAPN(F(SIM800_APN), F(SIM800_USER), F(SIM800_PASS));



}


void loop() {
    uint16_t status;
    uint32_t length;

    enable_led();
    Serial.println("Enabling Watchdog: ");
    disable_watchdog();

    while (!sim800.registerNetwork()) {
        Serial.println("Cycling the FONA for not registering on the network");
        sim800.shutdown();
        sim800.wakeup();
    }
    Serial.println("SIM800 network attached");


    if (!sim800.enableGPRS(50)) {
        Serial.println("SIM800 can't enable GPRS");
// halt(4);
    }
    Serial.println("SIM800 GPRS attached");

    // generate the server url from base and imei
    char url[strlen_P(SERVER_URL) + 16];
    char date;
    char time;
    char tz;
    sim800.time((char *) &date, (char *) &time, (char *) &tz);

    Serial.print("Date: ");
    Serial.println(date);
    Serial.print("Date length: ");
    Serial.println(strlen_P(date));

    Serial.print("Time: ");
    Serial.println(time);
    Serial.print("Time length: ");
    Serial.println(strlen_P(time));

    Serial.print("TZ: ");
    Serial.println(tz);
    Serial.print("TZ length: ");
    Serial.println(strlen_P(tz));

    strncpy_P(url, SERVER_URL, strlen_P(SERVER_URL));
    sim800.IMEI(url + strlen_P(SERVER_URL));


    Serial.print("URL: ");
    Serial.println(url);
    Serial.println("");

    status = sim800.HTTP_get(url, length);


    // remove erroneous content
    if(status != 200) {
        Serial.println("HTTP GET failed.");
    } else {
        Serial.println("HTTP GET successful!");
        Serial.print("Length: ");
        Serial.println(length);
    }




    /* Serial.println("Trying to shut down SIM800");
    while (!sim800.shutdown()) {
        Serial.println("Shutting down SIM800");
    }
     */

    while(!sim800.shutdown()) {
        Serial.println("Trying to shut down FONA");
    };

    disable_led();

    disable_watchdog();
    _delay_ms(30000);

}
