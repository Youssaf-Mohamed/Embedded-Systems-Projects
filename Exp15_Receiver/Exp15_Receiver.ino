
/*
  Exp15 Receiver: Receiving data using LoRa and displaying it on an LCD
  -----------------------------------------------------------------------------
  - This code initializes a LoRa receiver and displays received data on an I2C LCD.
  - The LoRa module operates at a frequency of 433 MHz.
  - Ensure the LCD address and LoRa module connections are correct before running.
  - Update LoRa frequency or LCD address if different from the default configuration.
*/


#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD definition
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address and LCD dimensions

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for the Serial Monitor

  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // LoRa frequency (433 MHz)
    Serial.println("LoRa init failed. Check your connections.");
    while (true);
  }

  // Initialize the LCD
  lcd.begin();
  lcd.backlight();
  lcd.print("LoRa Receiver");
}

void loop() {
  int packetSize = LoRa.parsePacket(); // Check for incoming LoRa packet
  if (packetSize) {
    char receivedChar = LoRa.read(); // Read the received character
    Serial.print("Received: ");
    Serial.println(receivedChar); // Display received data on Serial Monitor

    // Display the received data on the LCD
    lcd.clear();
    lcd.print("Received:");
    lcd.setCursor(0, 1);
    lcd.print(receivedChar);
  }
}
