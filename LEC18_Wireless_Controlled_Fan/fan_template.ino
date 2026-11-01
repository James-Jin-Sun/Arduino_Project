int motorPin_1 = 5; // DRV8833 IN1
int motorPin_2 = 6; // DRV8833 IN2

void setup()
{
    // put your setup code here, to run once:
    pinMode(motorPin_1, OUTPUT);
    pinMode(motorPin_2, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    // Forward at full speed
    analogWrite(motorPin_1, 255);
    analogWrite(motorPin_2, 0);
    delay(3000);
    
    //Forward at half speed
    analogWrite(motorPin_1, 128);
    analogWrite(motorPin_2, 0);
    delay(3000);

    // Stop
    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 0);
    delay(1000);

    // Reverse at full speed
    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 255);
    delay(3000);

    // Reverse at half speed
    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 128);
    delay(3000);
    
    // Stop
    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 0);
    delay(1000);
}