#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Time.h>
#include <SPI.h>

#define UVB_LIGHT_PIN 1
#define LIGHT_PIN 2
#define HEATING_PIN 3
#define HUMIDIFIER_1_PIN 4
#define HUMIDIFIER_2_PIN 5

const char* ssid = "ssid";
const char* password = "password";

const int allowedPins[] = {UVB_LIGHT_PIN, LIGHT_PIN, HEATING_PIN, HUMIDIFIER_1_PIN, HUMIDIFIER_2_PIN};

ESP8266WebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Define routing
void restServerRouting() {
  server.on("/get-pin-state", HTTP_GET, []() {
    char buffer[40];
    int id = server.arg("id").toInt();
    sprintf(buffer, "{\"id\":%i, \"state\":%i}", id, digitalRead(id));
    server.send(200, "text/json", buffer);
  });
  server.on("/set-pin-state", HTTP_POST, []() {
    char buffer[40];
    int id = server.arg("id").toInt();
    int value = server.arg("value").toInt();
    bool found = false;

    for (int i = 0; i < sizeof(allowedPins) / sizeof(*allowedPins); i++) {
        if (allowedPins[i] == id) {
          found = true;
          break;
        }
    }

    if (!found) {
      server.send(406, "text/json", "{\"message\":\"Invalid pin id provided.\"}");
      return;
    }

    digitalWrite(id, value ? HIGH : LOW);
    sprintf(buffer, "{\"id\":%i, \"state\":%i}", id, value);
    server.send(200, "text/json", buffer);
  });
}

// Manage not found URL
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}






void setup(void) {
  Serial.begin(9600);

  pinMode(UVB_LIGHT_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(HEATING_PIN, OUTPUT);
  pinMode(HUMIDIFIER_1_PIN, OUTPUT);
  pinMode(HUMIDIFIER_2_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set server routing
  restServerRouting();
  // Set not found response
  server.onNotFound(handleNotFound);
  // Start server
  server.begin();
  Serial.println("HTTP server started");

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(0);
  timeClient.update();
  setSyncProvider([]() {
    timeClient.update();
    return timeClient.getEpochTime();
  })
}

void loop(void) {
  server.handleClient();
}