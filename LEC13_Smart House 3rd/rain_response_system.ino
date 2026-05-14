#include <Arduino.h>

int rainPin = A1;
int rainValue = 0;
int rainThs = 500;

int servoPin = 10;
int winClosDeg = 0;
int winOpenDeg = 180;
Servo windowServo;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    windowServo.attach(servoPin); // attaches servo to pin 10
}

void loop()
{
    // put your main code here, to run repeatedly:
    rainValue = analogRead(rainPin);

    Serial.print("Rain Value: ");
    Serial.println(rainValue);

    if (rainValue > rainThs)
    {
        windowServo.write(winClosDeg); // Close the window
        Serial.println("Rain Detected! Closing the window.");
    }
    else
    {
        windowServo.write(winOpenDeg); // Open the window
        Serial.println("No Rain. Keeping the window open.");
    }

    delay(500);
}