/*
 Exp4v2 Transmitter
 -----------------------------------------------------------------------------
 -This experiment demonstrates a wireless communication system using nRF24L01. 
 -It transmits control signals ('F', 'B', 'S') based on button presses to control a remote device. 
 -An LED indicates the state of transmission.
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN pins for nRF24L01
const byte address[6] = "00001"; // Communication address

// Define button and LED pins
#define KEY1 2
#define KEY2 3
#define KEY3 4
#define LED_PIN 5

void setup() {
  // Set button pins as input with pull-up resistors
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize the radio
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); // Set power level to minimum
  radio.stopListening(); // Set as transmitter
}

void loop() {
  // Read button states
  bool key1State = !digitalRead(KEY1);
  bool key2State = !digitalRead(KEY2);
  bool key3State = !digitalRead(KEY3);

  // Send data based on button pressed
  if (key1State) {
    radio.write("F", 1); // Send 'F' for forward
    digitalWrite(LED_PIN, HIGH); // Turn on LED
  } else if (key2State) {
    radio.write("B", 1); // Send 'B' for backward
    digitalWrite(LED_PIN, HIGH); // Turn on LED
  } else if (key3State) {
    radio.write("S", 1); // Send 'S' for stop
    digitalWrite(LED_PIN, LOW); // Turn off LED
  } else {
    radio.write("S", 1); // Default to stop
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }
  delay(100); // Delay to avoid rapid sending
}
