#include <SPI.h>     // Library for SPI communication
#include <MFRC522.h> // Library for RFID reader

// Define RFID reader pins
int SS_PIN = 10;
int RST_PIN = 9;

// Create RFID reader object
MFRC522 rfid(SS_PIN, RST_PIN);

void setup()
{
    Serial.begin(9600); // Start Serial Monitor
    SPI.begin();        // Start SPI communication
    rfid.PCD_Init();    // Initialize RFID reader

    Serial.println("Scan your RFID card...");
}

void loop()
{
    // Step 1: Check if a new card is detected
    // If no card is found, exit loop() and try again
    if (!rfid.PICC_IsNewCardPresent())
    {
        return;
    }

    // Step 2: Read the card UID
    // If reading fails, exit loop() and try again
    if (!rfid.PICC_ReadCardSerial())
    {
        return;
    }

    // Step 3: Print the card UID
    Serial.print("Card UID: ");

    // A UID contains multiple bytes
    // Print each byte one by one
    for (int i = 0; i < rfid.uid.size; i++)
    {

        // Add a leading zero if the byte is less than 0x10
        // Example: 0x06 should display as 06
        if (rfid.uid.uidByte[i] < 0x10)
        {
            Serial.print("0");
        }

        // Print the byte in hexadecimal format
        Serial.print(rfid.uid.uidByte[i], HEX);
        Serial.print(" "); // Space between bytes
    }

    Serial.println(); // Move to next line

    // Step 4: Stop communication with this card
    rfid.PICC_HaltA();
}
