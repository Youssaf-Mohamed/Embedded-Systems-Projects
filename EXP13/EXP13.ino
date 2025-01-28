/*
  EXP13: Control water pump and read soil moisture using ESP32 and MQTT
  -----------------------------------------------------------------------------
  1. The code connects to a Wi-Fi network using the provided SSID and password.
  2. It connects to the MQTT broker to publish moisture data and control the pump.
  3. Reads soil moisture sensor data from pin 34 and publishes it to the topic "sensor/moisture".
  4. Controls the pump via MQTT messages received on the topic "pump/control" (ON/OFF).
  5. Update the following lines with your own values:
     - Line 8: const char* ssid = "YOUR_WIFI_SSID"; // Replace with your Wi-Fi SSID
     - Line 9: const char* password = "YOUR_WIFI_PASSWORD"; // Replace with your Wi-Fi password
     - Line 12: const char* mqtt_server = "MQTT_BROKER_IP"; // Replace with your MQTT broker IP
     - Line 13: const int mqtt_port = 1883; // Replace if using a non-default port
     - Line 14: const char* mqtt_user = "MQTT_USERNAME"; // Replace with your MQTT username (if needed)
     - Line 15: const char* mqtt_password = "MQTT_PASSWORD"; // Replace with your MQTT password (if needed)

     by: Youssaf Mohamed Ali 
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Wi-Fi credentials
const char* ssid = "TP-Guest";
const char* password = "88888888";

// MQTT broker details
const char* mqtt_server = "MQTT_BROKER_IP";
const int mqtt_port = 1883;
const char* mqtt_user = "MQTT_USERNAME";
const char* mqtt_password = "MQTT_PASSWORD";

// OLED configuration
#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  
#define OLED_RESET    -1  
#define SCREEN_ADDRESS 0x3C  

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
const int moisturePin = 34;  
const int pumpPin1 = 26;     
const int pumpPin2 = 27;     

// Variables
WiFiClient espClient;
PubSubClient client(espClient);
int moistureValue = 0;
String pumpStatus = "OFF";

void setup_wifi() {
    delay(10);
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi connected");
}

void reconnect() {
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
            Serial.println("MQTT connected");
            client.subscribe("pump/control");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    String message = "";
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    if (String(topic) == "pump/control") {
        if (message == "ON") {
            digitalWrite(pumpPin1, HIGH);
            digitalWrite(pumpPin2, LOW);
            pumpStatus = "ON";
            Serial.println("Pump turned ON");
        } else if (message == "OFF") {
            digitalWrite(pumpPin1, LOW);
            digitalWrite(pumpPin2, LOW);
            pumpStatus = "OFF";
            Serial.println("Pump turned OFF");
        }
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(moisturePin, INPUT);
    pinMode(pumpPin1, OUTPUT);
    pinMode(pumpPin2, OUTPUT);

    // Initialize OLED
    Wire.begin(25, 22);  
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("Failed to initialize OLED!"));
        for(;;);
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 25);
    display.print("Starting...");
    display.display();  

    // Connect to Wi-Fi
    setup_wifi();

    // Set up MQTT
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void displayOLED() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 10);
    display.print("Moisture: ");
    display.println(moistureValue);

    display.setCursor(0, 30);
    display.print("Pump: ");
    display.println(pumpStatus);

    display.display();
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Read moisture sensor
    moistureValue = analogRead(moisturePin);
    Serial.print("Moisture Value: ");
    Serial.println(moistureValue);

    // Publish moisture data to MQTT
    char moistureStr[8];
    sprintf(moistureStr, "%d", moistureValue);
    client.publish("sensor/moisture", moistureStr);

    // Update OLED display
    displayOLED();

    delay(5000);
}