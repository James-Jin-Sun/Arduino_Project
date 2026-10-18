
#include <SPI.h>
#include <MFRC522.h>

// Define RFID reader pins
int SS_PIN = 10;
int RST_PIN = 9;

// Create RFID reader object
MFRC522 rfid(SS_PIN, RST_PIN);

// Store authorized card UID in a byte array
// Replace these values with your own card UID
byte allowedUid[4] = {0xE5, 0x96, 0x69, 0x06};

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
    if (!rfid.PICC_IsNewCardPresent())
    {
        return;
    }

    // Step 2: Read the card UID
    if (!rfid.PICC_ReadCardSerial())
    {
        return;
    }

    // Step 3: Print card UID
    Serial.print("Card UID: ");

    for (int i = 0; i < rfid.uid.size; i++)
    {
        // Add leading zero for single-digit hex values
        if (rfid.uid.uidByte[i] < 0x10)
        {
            Serial.print("0");
        }

        Serial.print(rfid.uid.uidByte[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Step 4: Compare scanned UID with authorized UID

    // Assume access is granted at first
    bool accessGranted = true;

    // Check if the UID length is correct (4 bytes)
    if (rfid.uid.size != 4)
    {
        accessGranted = false;
    }
    else
    {

        // Compare each byte of the two UIDs
        for (int i = 0; i < 4; i++)
        {

            // If any byte is different, deny access
            if (rfid.uid.uidByte[i] != allowedUid[i])
            {
                accessGranted = false;
            }
        }
    }

    // Step 5: Display verification result
    if (accessGranted)
    {
        Serial.println("Access Granted");
    }
    else
    {
        Serial.println("Access Denied");
    }

    // Step 6: Stop communication with this card
    rfid.PICC_HaltA();
}
