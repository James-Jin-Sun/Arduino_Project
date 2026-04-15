int redLED = 10;
int yellowLED = 9;
int greenLED = 8;

void setup()
{
    pinMode(redLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
}

void loop()
{
    // Green
    digitalWrite(greenLED, HIGH);
    delay(2000);
    digitalWrite(greenLED, LOW);
    // Yellow
    for (int i = 0; i < 2; i++)
    {
        delay(500);
        digitalWrite(yellowLED, HIGH);
        delay(500);
        digitalWrite(yellowLED, LOW);
    }
    // Red
    digitalWrite(redLED, HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
}
