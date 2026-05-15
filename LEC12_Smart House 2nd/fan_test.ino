int motorPin_1 = 5;  // DRV8833 IN1
int motorPin_2 = 9;  // DRV8833 IN2

void setup()
{
    // put your setup code here, to run once:
    pinMode(motorPin_1, OUTPUT);
    pinMode(motorPin_2, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    analogWrite(motorPin_1, 255);
    analogWrite(motorPin_2, 0); // full speed cooling fan
    delay(5000);
    analogWrite(motorPin_1, 153);
    analogWrite(motorPin_2, 0); // half speed cooling fan
    delay(5000);

    // allow fan to slow down before switching direction
    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 0); // stop motor: both inputs LOW
    delay(2000);

    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 255); // full speed exhaust fan
    delay(5000);
    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 153); // half speed exhaust fan
    delay(5000);

    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 0); // stop motor: both inputs LOW
    delay(2000);
}