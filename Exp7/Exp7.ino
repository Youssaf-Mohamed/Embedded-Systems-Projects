/*
  Exp7: Water Level Monitoring System: Using Ultrasonic Sensor and LCD Display
  ----------------------------------------------------------------------------
  - This system uses an ultrasonic sensor to measure the water level in a tank.
  - The level is displayed on an LCD screen and alerts are triggered via a buzzer and LED.
  - The system measures the distance to the water surface and calculates the water level.
  - If the water level is below the ALERT_LEVEL_CM threshold, the buzzer and LED are activated.
  - Make sure to connect the ultrasonic sensor, LCD, and other components correctly.
  - Adjust the TANK_HEIGHT_CM and ALERT_LEVEL_CM values according to your tank's specifications.
*/


#include <LiquidCrystal.h>

// Define LCD pins (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Define ultrasonic sensor pins
const int trigPin = 11;
const int echoPin = 10;

// Define buzzer and LED pins
const int buzzerPin = 8;
const int ledPin = 11;

// Constants
const int TANK_HEIGHT_CM = 100; // Replace with actual tank height
const int ALERT_LEVEL_CM = 50;  // Water level threshold for alerts

// Variables
long duration;
int distance;
int waterLevel;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Water Level:");

  // Initialize ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize buzzer and LED
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600); // For debugging
}

void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // Validate distance (avoid negative values or out-of-range readings)
  if (distance <= 0 || distance > TANK_HEIGHT_CM) {
    lcd.setCursor(0, 1);
    lcd.print("Error:Check Sensor");
    tone(buzzerPin,800,1200);
    tone(buzzerPin,800,400);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    return; // Skip invalid readings
  }

  // Calculate water level (sensor at top of tank)
  waterLevel = TANK_HEIGHT_CM - distance;

  // Display water level on LCD
  lcd.setCursor(0, 1);
  lcd.print("Level: ");
  lcd.print(waterLevel);
  lcd.print(" cm   "); // Extra spaces to clear old characters

  // Control buzzer and LED
  if (waterLevel < ALERT_LEVEL_CM) {
    digitalWrite(buzzerPin, HIGH); // For active buzzer
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(500); // Adjust delay as needed
}