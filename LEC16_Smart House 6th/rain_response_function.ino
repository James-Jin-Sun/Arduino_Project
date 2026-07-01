#include <Servo.h> // use Servo library

int rainPin = A1;
int rainValue = 0;
int lightRainThs = 700; // light rain threshold
int heavyRainThs = 400; // heavy rain threshold

int servoPin = 10;
int winClosDeg = 0;
int winHalfDeg = 90;
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
    handleRainResponse();
}

void handleRainResponse()
{
    rainValue = analogRead(rainPin);
    Serial.print(F("Rain Value: "));
    Serial.println(rainValue);

    if (rainValue > lightRainThs)
    {
        // No rain
        windowServo.write(winOpenDeg); // Open the window
        Serial.println(F("No Rain. Keeping the window open."));
    }
    else if (rainValue <= lightRainThs && rainValue > heavyRainThs)
    {
        // Light rain
        windowServo.write(winHalfDeg); // Partially open the window
        Serial.println(F("Light Rain Detected! Partially opening the window."));
    }
    else // rainValue <= heavyRainThs
    {
        // Heavy rain
        windowServo.write(winClosDeg); // Close the window
        Serial.println(F("Heavy Rain Detected! Closing the window."));
    }
    delay(500);
}