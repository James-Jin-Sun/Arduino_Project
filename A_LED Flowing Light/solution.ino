int ledPin[6] = {2, 3, 4, 5, 6, 7};
int numLedPins = 6;

void setup()
{
    for (int i = 0; i < numLedPins; i++)
    {
        pinMode(ledPin[i], OUTPUT);
    }
}

void loop()
{
    // ON: Turn all LEDs on at the same time
    for (int i = 0; i < numLedPins; i++)
    {
        digitalWrite(ledPin[i], HIGH);
    }
    delay(1000); // Wait for 1s

    // OFF: Turn all LEDs off at the same time
    for (int i = 0; i < numLedPins; i++)
    {
        digitalWrite(ledPin[i], LOW);
    }
    delay(1000); // Wait for 1s

    // Flow from left to right: Turn on one LED
    // at a time from the leftmost LED to the rightmost
    for (int i = 0; i < numLedPins; i++)
    {
        digitalWrite(ledPin[i], HIGH);
        delay(200);
        digitalWrite(ledPin[i], LOW);
    }
    delay(200);

    // Flow from right to left: Turn on one LED
    // at a time from the rightmost LED to the leftmost
    for (int i = numLedPins - 1; i >= 0; i--)
    {
        digitalWrite(ledPin[i], HIGH);
        delay(200);
        digitalWrite(ledPin[i], LOW);
    }
    delay(200);
}