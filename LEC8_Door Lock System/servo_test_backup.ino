#include <Servo.h>
int servoPin = 13;
byte servoDeg[3] = {0, 90, 180};
Servo myServo;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    myServo.attach(servoPin);
}

void loop()
{
    // put your main code here, to run repeatedly:
    for (int i = 0; i < 3; i++)
    {
        myServo.write(servoDeg[i]);
        Serial.print("Current servo degree: ");
        Serial.println(servoDeg[i]);
        delay(1000);
    }
    delay(1000);
}
