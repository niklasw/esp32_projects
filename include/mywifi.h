#include <WiFi.h>

void wifi_info()
{
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void wifi_keep_connected()
{
    while (WiFi.status() != WL_CONNECTED) {
        delay(5000);
        Serial.println("WiFi lost. Reconnecting");
        WiFi.reconnect();
    }
    wifi_info();
}

void wifi_setup(const char* ssid, const char* password)
{
    delay(10);
    Serial.println("Setting up WiFi");
    Serial.println();
    Serial.print("WiFi connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    wifi_info();
}
