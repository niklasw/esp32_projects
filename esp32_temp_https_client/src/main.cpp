#include <Arduino.h>
#include <string.h>
#include "myhttpclient.h"
#include "TSensors.h"
#include "config.h"

const char* httpsServer = WEB_SERVER_ADDRESS;
uint16_t httpsPort = WEB_SERVER_PORT;

TSensors* tsPtr;

String apiTarget = "/api/strudeviken?measurement=";

void setup() {
    Serial.begin(BAUD);
    wifi_setup(ESSID, WEP_KEY);

    tsPtr = new TSensors(ONE_WIRE_BUS);
    tsPtr->mkTopics(MQTT_TOPIC);
}

void loop() {
    wifi_keep_connected();

    tsPtr->info();

    tsPtr->requestTemperatures();

    for (int i=0; i < tsPtr->nSensors(); i++)
    {
        String apiRequest = apiTarget + tsPtr->address(i)
                          + "&value=" + tsPtr->temperature(i);

        String reply = httpRequest
        (
            httpsServer,
            httpsPort,
            apiRequest.c_str(),
            WEB_BASIC_AUTH
        );
    }

    String apiRequest = apiTarget + "nsensors&value=" + tsPtr->nSensors();

    String reply = httpRequest
    (
        httpsServer,
        httpsPort,
        apiRequest.c_str(),
        WEB_BASIC_AUTH
    );

    Serial.println(reply);

    delay(LOOP_PERIOD*1000);
}
