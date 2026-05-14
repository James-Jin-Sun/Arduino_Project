#include <Servo.h> // use Servo library
int servoPin = 10;
int servoDegree = 180;
Servo myServo; // create servo object to control a servo

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    myServo.attach(servoPin); // attaches servo to pin 10
    Serial.print("Current servo degree: ");
    Serial.println(servoDegree);
}

void loop()
{
    // put your main code here, to run repeatedly:
    myServo.write(servoDegree);
}
