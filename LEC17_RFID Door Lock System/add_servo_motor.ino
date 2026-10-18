
#include <SPI.h>     // SPI communication
#include <MFRC522.h> // RFID reader
#include <Servo.h>   // Servo motor control

// Define pins
int SS_PIN = 10;
int RST_PIN = 9;
int SERVO_PIN = 6;

// Create RFID reader and servo objects
MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorServo;

// Authorized card UID
// Replace with your own card UID
byte allowedUid[4] = {0xE5, 0x96, 0x69, 0x06};

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();

    // Connect servo to its signal pin
    doorServo.attach(SERVO_PIN);

    // Set servo to locked position (0 degrees)
    doorServo.write(0);

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

        if (rfid.uid.uidByte[i] < 0x10)
        {
            Serial.print("0");
        }

        Serial.print(rfid.uid.uidByte[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Step 4: Verify card UID

    // Assume the card is authorized
    bool accessGranted = true;

    // Check if the UID has exactly 4 bytes
    if (rfid.uid.size != 4)
    {
        accessGranted = false;
    }
    else
    {

        // Compare each UID byte
        for (int i = 0; i < 4; i++)
        {

            // Deny access if any byte is different
            if (rfid.uid.uidByte[i] != allowedUid[i])
            {
                accessGranted = false;
            }
        }
    }

    // Step 5: Control servo based on verification

    if (accessGranted)
    {
        Serial.println("Access Granted");

        // Rotate servo to 90 degrees to unlock
        doorServo.write(90);

        // Keep door unlocked for 3 seconds
        delay(3000);

        // Rotate servo back to 0 degrees to lock
        doorServo.write(0);
    }
    else
    {
        // Unauthorized card: keep door locked
        Serial.println("Access Denied");
    }

    // Step 6: Stop communication with this card
    rfid.PICC_HaltA();
}
