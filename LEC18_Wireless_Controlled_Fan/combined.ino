#include <SoftwareSerial.h>

// Bluetooth module connections
// Arduino D3 (RX) <- JDY-16 TXD
// Arduino D2 (TX) -> JDY-16 RXD (level shifted)
SoftwareSerial bluetooth(3, 2);

// DRV8833 motor driver pins
int motorIN1 = 5;
int motorIN2 = 6;

// Fan settings
int fanSpeed = 0;        // PWM: 0 to 255
bool blowingMode = true; // true = Blow, false = Exhaust

void setup()
{
    // Set motor driver pins as outputs
    pinMode(motorIN1, OUTPUT);
    pinMode(motorIN2, OUTPUT);

    // Fan initially stopped
    updateFan();

    // Start serial communication
    Serial.begin(9600);
    bluetooth.begin(9600);

    Serial.println("Bluetooth Fan Ready!");
    Serial.println("B = Blow, E = Exhaust");
    Serial.println("1 = Medium, 2 = High");
    Serial.println("0 = Stop");
}

void loop()
{

    // Check if Bluetooth command is received and process it
    if (bluetooth.available()) // check if there is still data available
    {

        char command = bluetooth.read();

        Serial.print("Received: ");
        Serial.println(command);

        // Process Bluetooth commands
        switch (command)
        {

        case 'B':
        case 'b':
            fanSpeed = 0; // Stop before changing mode
            updateFan();
            blowingMode = true;
            Serial.println("Blowing Mode Selected");
            break;

        case 'E':
        case 'e':
            fanSpeed = 0; // Stop before changing mode
            updateFan();
            blowingMode = false;
            Serial.println("Exhaust Mode Selected");
            break;

        case '1':
            fanSpeed = 128;
            Serial.println("Medium Speed");
            break;

        case '2':
            fanSpeed = 255;
            Serial.println("High Speed");
            break;

        case '0':
            fanSpeed = 0;
            Serial.println("Fan Stopped");
            break;

        default:
            // Ignore unknown commands
            return;
        }

        // Update motor based on selected mode and speed
        updateFan();
    }
}

// Function to control fan motor
void updateFan()
{

    // Stop fan
    if (fanSpeed == 0)
    {
        analogWrite(motorIN1, 0);
        analogWrite(motorIN2, 0);
    }

    // Blowing mode: forward rotation
    else if (blowingMode == true)
    {
        analogWrite(motorIN1, fanSpeed);
        analogWrite(motorIN2, 0);
    }

    // Exhaust mode: reverse rotation
    else
    {
        analogWrite(motorIN1, 0);
        analogWrite(motorIN2, fanSpeed);
    }
}
