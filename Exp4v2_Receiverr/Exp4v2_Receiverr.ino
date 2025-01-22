/*
  Exp4v2 Receiver
  -------------------------------------------------------------------------------
  - This experiment demonstrates a wireless control system using nRF24L01 and an OLED display.
  - Commands ('F', 'B', 'S') are received wirelessly to control motor directions or stop.
  - An OLED display provides real-time feedback on the received commands and system status.
  - Ensure proper wiring for the nRF24L01, motor driver, and OLED display for correct operation.
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

RF24 radio(7, 8); // CE, CSN pins for nRF24L01
const byte address[6] = "00001"; // Same address as transmitter

// Define motor driver pins
#define IN1 10
#define IN2 9
#define IN3 6
#define IN4 5

// Define OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize motor driver pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotor(); // Stop motor initially

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("System Ready!");
  display.display();

  // Initialize the radio
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN); // Set power level to minimum
  radio.startListening(); // Set as receiver
}

void loop() {
  if (radio.available()) {
    char command;
    radio.read(&command, sizeof(command));
    
    display.clearDisplay();
    display.setCursor(0, 0);

    // Execute commands based on received data
    switch (command) {
      case 'F':
        forward();
        display.println("Moving Forward");
        break;
      case 'B':
        backward();
        display.println("Moving Backward");
        break;
      case 'S':
        stopMotor();
        display.println("Stopped");
        break;
    }
    display.display();
  }
}

// Motor control functions
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
