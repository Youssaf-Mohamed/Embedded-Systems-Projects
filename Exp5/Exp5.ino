/*
  Exp5: RFID Access System: Control System with RFID, Audio, and LCD
  -----------------------------------------------------------------------------
  - This system uses an RFID reader to control access based on a stored card UID.
  - If the UID matches the allowed card, the solenoid unlocks, and an audio file is played.
  - The system uses LEDs to indicate the status: red for standby and blue for access granted.
  - A DFPlayer module is used to play audio files upon certain events (access granted/denied).
  - Ensure all components are correctly connected, including RFID reader, LCD, solenoid, LEDs, and DFPlayer.
*/


#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal.h>

// Define LCD pins
// const int RS = 7, EN = 2, D4 = 3, D5 = 4, D6 = 5, D7 = 6;
// LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Define LCD pins (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 2, 3, 4, 5, 6);

// Define RFID pins
#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Define DFPlayer pins
SoftwareSerial mySoftwareSerial(8, 9); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Define control pins
const int solenoidPin = 8; // Solenoid control pin
const int ledRed = A1;      // Red LED
const int ledBlue = A2;     // Blue LED

// Allowed card UID (replace with your card's UID)
byte allowedUID[] = {0xDE, 0xAD, 0xBE, 0xEF};

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("System Ready");
  
  // Initialize RFID
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Initialize DFPlayer
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    lcd.clear();
    lcd.print("DFPlayer Error!");
    while(true);
  }
  myDFPlayer.volume(30); // Set volume (0-30)
  
  // Initialize pins
  pinMode(solenoidPin, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  digitalWrite(solenoidPin, LOW);
  digitalWrite(ledRed, HIGH); // Red LED in standby mode
}

void loop() {
  // Check for a new card
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Read UID
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }

  // Check if the card is allowed
  bool isAllowed = true;
  for (byte i = 0; i < 4; i++) {
    if (mfrc522.uid.uidByte[i] != allowedUID[i]) {
      isAllowed = false;
      break;
    }
  }

  // Execute actions based on card validity
  if (isAllowed) {
    lcd.clear();
    lcd.print("Welcome!");
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(solenoidPin, HIGH); // Unlock the solenoid
    myDFPlayer.play(1); // Play audio file 1
    delay(3000); // Wait for 3 seconds
    digitalWrite(solenoidPin, LOW); // Lock the solenoid
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, HIGH);
  } else {
    lcd.clear();
    lcd.print("Access Denied!");
    digitalWrite(ledRed, HIGH);
    myDFPlayer.play(2); // Play audio file 2
    delay(2000);
  }
  
  lcd.clear();
  lcd.print("System Ready");
  mfrc522.PICC_HaltA();
}