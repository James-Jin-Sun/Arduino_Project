
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Define pins
int SS_PIN = 10;
int RST_PIN = 9;
int SERVO_PIN = 6;

// Create RFID reader and servo objects
MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorServo;

// Authorized card UID
byte allowedUid[4] = {0xE5, 0x96, 0x69, 0x06};

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();

    // Initialize servo motor
    doorServo.attach(SERVO_PIN);
    doorServo.write(0); // Locked position

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

    // Step 4: Verify UID using our function
    bool accessGranted = verifyUid(
        rfid.uid.uidByte,
        rfid.uid.size);

    // Step 5: Control servo motor
    if (accessGranted)
    {
        Serial.println("Access Granted");

        doorServo.write(90); // Unlock
        delay(3000);         // Wait 3 seconds
        doorServo.write(0);  // Lock again
    }
    else
    {
        Serial.println("Access Denied");
    }

    // Step 6: Finish reading
    rfid.PICC_HaltA();
}

// Function: Verify RFID card UID
// Input: scanned UID array and UID length
// Output: true (authorized) or false (denied)
bool verifyUid(byte scannedUid[], int uidSize)
{

    // Check if UID length is correct
    if (uidSize != 4)
    {
        return false;
    }

    // Compare each byte with the authorized UID
    for (int i = 0; i < 4; i++)
    {

        // If any byte is different, return false
        if (scannedUid[i] != allowedUid[i])
        {
            return false;
        }
    }

    // All bytes match, return true
    return true;
}