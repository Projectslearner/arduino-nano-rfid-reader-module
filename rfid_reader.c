/*
    Project name : RFID Reader Module
    Modified Date: 12-06-2024
    Code by : Projectslearner
    Website : https://projectslearner.com/learn/arduino-nano-rfid-reader-module
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  Serial.println("Scan your RFID card/tag");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show some details of the card
  Serial.print("UID tag: ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();

  // Check if the UID is valid
  if (isValidRFID(content)) {
    Serial.println("This is a valid RFID tag.");
  } else {
    Serial.println("This is not a valid RFID tag.");
  }

  delay(1000);  // Add a delay to avoid reading the same card multiple times
}

bool isValidRFID(String uid) {
  // Add the valid RFID tags here
  String validRFID[] = {" 0A 1B 2C 3D", " 12 34 56 78"}; // Example UIDs, replace with your valid UIDs

  for (int i = 0; i < sizeof(validRFID) / sizeof(validRFID[0]); i++) {
    if (uid.equalsIgnoreCase(validRFID[i])) {
      return true;
    }
  }
  return false;
}
