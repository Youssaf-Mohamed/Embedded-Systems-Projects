/*
  Exp2: Fan Control System with Temperature and Joystick Input
  -----------------------------------------------------------------------------
  - This system uses a DS18B20 temperature sensor to monitor the temperature.
  - The fan speed is controlled via a joystick, and the speed is mapped to a PWM output.
  - The fan's speed is constrained to avoid stopping completely.
  - An LED lights up when the fan is running, and temperature data is displayed on an LCD.
  - Ensure correct wiring of the temperature sensor, joystick, fan, and LED.
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Define LCD pins
const int RS = 2, EN = 3, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
LiquidCrystal lcd(10, 8, 7, 6, 5, 4);

// Define DS18B20 temperature sensor pins
#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Define joystick, fan, and LED pins
const int joystickY = A5;   // Y-axis of the joystick
const int fanPWM = 3;       // PWM pin for the fan (IRFZ44N)
const int ledPin = 2;      // Red LED pin

// System variables
int fanSpeed = 0;
float temperature = 0;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  
  // Initialize temperature sensor
  sensors.begin();
  
  // Set output pins
  pinMode(fanPWM, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  // Startup message
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Read temperature
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  
  // Read joystick value and map it to fan speed (0-255)
  int joyValue = analogRead(joystickY);
  fanSpeed = map(joyValue, 0, 1023, 0, 255);
  
  // Apply minimum fan speed (50/255) to prevent it from stopping
  fanSpeed = constrain(fanSpeed, 50, 255);
  
  // Control fan and LED
  analogWrite(fanPWM, fanSpeed);
  digitalWrite(ledPin, fanSpeed > 0 ? HIGH : LOW);
  
  // Display data on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223);  // Celsius degree symbol
  lcd.print("C  ");
  
  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  lcd.print(map(fanSpeed, 0, 255, 0, 100)); // Convert speed to percentage
  lcd.print("%   ");
  
  delay(100); // Short delay to improve responsiveness
}
