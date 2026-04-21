int redLED = 2;
int orangeLED = 3;
int yellowLED = 4;
int greenLED = 5;
int blueLED = 6;

void setup()
{
    pinMode(redLED, OUTPUT);
    pinMode(orangeLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
}

void loop()
{
    // ON: Turn all LEDs on at the same time
    digitalWrite(redLED, HIGH);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, HIGH);
    delay(1000); // Wait for 1s

    // OFF: Turn all LEDs off at the same time
    digitalWrite(redLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    delay(1000); // Wait for 1s

    // Flow from left to right: Turn on one LED
    // at a time from the leftmost LED to the rightmost
    digitalWrite(redLED, HIGH);
    delay(200);
    digitalWrite(redLED, LOW);
    digitalWrite(orangeLED, HIGH);
    delay(200);
    digitalWrite(orangeLED, LOW);
    digitalWrite(yellowLED, HIGH);
    delay(200);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
    delay(200);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
    delay(200);
    digitalWrite(blueLED, LOW);
    delay(200);

    // Flow from right to left: Turn on one LED
    // at a time from the rightmost LED to the leftmost
    digitalWrite(blueLED, HIGH);
    delay(200);
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, HIGH);
    delay(200);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    delay(200);
    digitalWrite(yellowLED, LOW);
    digitalWrite(orangeLED, HIGH);
    delay(200);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED, HIGH);
    delay(200);
    digitalWrite(redLED, LOW);
    delay(200);
}