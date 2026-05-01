#include <Servo.h>

int trigPin = 2;
int echoPin = 3;
unsigned long duration;
int distance;
int servoPin = 4;
Servo myServo;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    myServo.attach(servoPin);
}

void loop()
{
    // put your main code here, to run repeatedly:
    for (int angle = 0; angle <= 180; angle++)
    {
        myServo.write(angle);
        measureDistance();
        Serial.print("Angle: ");
        Serial.print(angle);
        Serial.print("° | ");
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
        delay(60); // give servo time to move
    }

    for (int angle = 180; angle >= 0; angle--)
    {
        myServo.write(angle);
        measureDistance();
        Serial.print("Angle: ");
        Serial.print(angle);
        Serial.print("° | ");
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
        delay(60); // give servo time to move
    }
}

void measureDistance()
{
    digitalWrite(trigPin, LOW); // make sure trigger pin starts LOW
    delayMicroseconds(2);       // ensures a clean LOW

    // step 1:send a 10ms trigger pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // step 2: measure how long Echo pin stays HIGH
    duration = pulseIn(echoPin, HIGH);
    // step 3: convert time to distance
    distance = duration * 0.0343 / 2;
}