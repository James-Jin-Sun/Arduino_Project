int motorPin = 5;

void setup()
{
    // put your setup code here, to run once:
    pinMode(motorPin, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    analogWrite(motorPin, 255);
    delay(5000);
    analogWrite(motorPin, 153);
    delay(5000);
    analogWrite(motorPin, 0);
    delay(2000);
}