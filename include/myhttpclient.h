
#include "mywifi.h"
#include <WiFiClientSecure.h>


String httpConsumeHeader(WiFiClientSecure* client)
{
    String header = "";
    while (client->connected())
    {
        String line = client->readStringUntil('\n');
        if (line == "\r")
        {
            Serial.println("Hdrs ok");
            break;
        }
        else
        {
            header = line;
        }
        delay(10);
    }
    return header;
}


String httpRequest(const char* host,
                 uint16_t port,
                 const char* path,
                 const char* basicAuth,
                 const char* method = "GET")
{
    WiFiClientSecure client;

    client.setInsecure();

    String reply;

    if (client.connect(host, port))
    {
        Serial.println("Connected to server");
        client.print("GET ");
        client.print(path);
        client.println(" HTTP/1.1");
        client.print("Authorization: Basic ");
        client.println(basicAuth);
        client.print("Host: ");
        client.println(host);
        client.println("Connection: close");
        client.println();

        String header = httpConsumeHeader(&client);

        while (client.available())
        {
            char c = client.read();
            reply += c;
        }
    }
    else
    {
      Serial.println("Connection failed");
      return String();
    }
    reply.trim();
    return reply;
}
