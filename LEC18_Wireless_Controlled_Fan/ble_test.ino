#include <SoftwareSerial.h>

// Bluetooth module connections
// Arduino D3 (RX) <- JDY-16 TXD
// Arduino D2 (TX) -> JDY-16 RXD
SoftwareSerial bluetooth(3, 2);

void setup()
{
    // Start communication with computer
    Serial.begin(9600);

    // Start communication with Bluetooth module
    bluetooth.begin(9600);

    Serial.println("JDY-16 Bluetooth Test Ready!");
    Serial.println("Send a message from your phone.");
}

void loop()
{

    // Receive data from Bluetooth and print to Serial Monitor
    while (bluetooth.available())
    {
        char data = bluetooth.read(); // bluetooth.read() only reads one character at a time
        Serial.write(data);  // Print received Bluetooth data to Serial Monitor
    }

    // Send data from Serial Monitor to Bluetooth
    while (Serial.available())
    {
        char data = Serial.read();
        bluetooth.write(data);  // Send data from Serial Monitor to Bluetooth
    }
}
