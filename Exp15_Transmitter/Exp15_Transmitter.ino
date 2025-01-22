/*
  Exp15 Transmitter: Sending data using LoRa and Keypad input
  -----------------------------------------------------------------------------
  - This code initializes a 4x3 keypad and sends the pressed key to a LoRa receiver.
  
*/

#include <SPI.h>
#include <LoRa.h>
#include <Keypad.h>

// Keypad definition
const byte ROWS = 4; // Number of rows
const byte COLS = 3; // Number of columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; // Pins connected to the rows
byte colPins[COLS] = {6, 7, 8};    // Pins connected to the columns
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for the Serial Monitor

  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // LoRa frequency (433 MHz)
    Serial.println("LoRa init failed. Check your connections.");
    while (true);
  }
}

void loop() {
  char key = keypad.getKey(); // Read key from keypad
  if (key) { // If a key is pressed
    Serial.print("Sending: ");
    Serial.println(key); // Display the key on Serial Monitor
    LoRa.beginPacket(); // Start LoRa packet
    LoRa.print(key);    // Add the key to the packet
    LoRa.endPacket();   // Send the packet
  }
}
