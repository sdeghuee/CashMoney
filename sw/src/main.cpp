#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "../lib/HTTPSRedirect.h"
#include "../lib/HTTPSRedirect.cpp"
#include "../lib/DebugMacros.h"
#include "EEPROM.h"
#define LED 13

const char* ssid = "Samfi";
const char* pass = "thankssam";
const char* host = "script.google.com";
const char *GScriptId = "AKfycbwEsXsFMK3IN--sRA744hEnfrrkNBfR_kRLBwqpZd65VPnONtU";
const int httpsPort = 443;
const char* fingerprint = "36:AC:88:A3:6C:C6:21:C2:02:D5:AA:B9:E7:06:74:3C:BC:F4:F9:00";
uint addr = 0;

  // fake data
  struct { 
    uint val = 0;
    char str[20] = "";
  } data;

String url = String("/macros/s/") + GScriptId + "/exec";

HTTPSRedirect* client = nullptr;

int payDelay = 20;

void setup() {
    EEPROM.begin(512);
    pinMode(LED,OUTPUT);
    Serial.begin(9600);
    Serial.println("Hello World!");
    digitalWrite(LED,1);
    WiFi.begin(ssid, pass);             // Connect to the network
    int bypass = 10;
    while (WiFi.status() != WL_CONNECTED && bypass) { // Wait for the Wi-Fi to connect
        delay(1000);
        bypass--;
  }
    if(bypass != 0)
    {
        client = new HTTPSRedirect(httpsPort);
        client->setPrintResponseBody(true);
        client->setContentTypeHeader("application/json");
        client = new HTTPSRedirect(httpsPort);
        client->setPrintResponseBody(true);
        client->setContentTypeHeader("application/json");
        bool flag = false;
        for (int i=0; i<5; i++){
            int retval = client->connect(host, httpsPort);
            if (retval == 1) {
                flag = true;
                break;
            }
        }
        client->GET(url, host);
        payDelay = client->getResponseBody().toInt();
        data.val = payDelay;
        EEPROM.put(addr,data);
        EEPROM.commit();
        Serial.print("This is the get");
        Serial.println(payDelay);
        delete client;
        client = nullptr;
    }
    else{
          EEPROM.get(addr,data);
          payDelay = data.val;

    }
}
void loop(){
    digitalWrite(LED,1);
    delay(1000);
    digitalWrite(LED,0);
    delay(payDelay);
}
