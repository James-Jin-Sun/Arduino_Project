int orangeLED = 2;
int blueLED = 3;
int greenLED = 4; // newly added LED

void setup()
{
    pinMode(orangeLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
    pinMode(greenLED, OUTPUT); // setup for new LED
}

void loop()
{
    // ON
    digitalWrite(orangeLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, HIGH);
    delay(2000); // Wait for 1s

    // Simultaneous blinking
    for (int i = 0; i < 2; i++)
    {
        digitalWrite(orangeLED, LOW);
        digitalWrite(blueLED, LOW);
        digitalWrite(greenLED, LOW);
        delay(500);

        digitalWrite(orangeLED, HIGH);
        digitalWrite(blueLED, HIGH);
        digitalWrite(greenLED, HIGH);
        delay(500);
    }

    // Sequential blinking
    for (int i = 0; i < 2; i++)
    {
        digitalWrite(orangeLED, HIGH);
        delay(500);
        digitalWrite(orangeLED, LOW);

        digitalWrite(blueLED, HIGH);
        delay(500);
        digitalWrite(blueLED, LOW);

        digitalWrite(greenLED, HIGH);
        delay(500);
        digitalWrite(greenLED, LOW);
    }

    // Off
    digitalWrite(orangeLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, LOW);
    delay(2000); // Wait for 1s
}