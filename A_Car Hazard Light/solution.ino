// =========================
// Rear-view car light system
// =========================

int buttonPin = 2;   // interrupt pin
int whiteLight = 3;  // lower white constant ON
int yellowLight = 5; // yellow hazard light
int buzzerPin = 6;   // passive buzzer
int redLight = 4;    // upper red  constant ON

// hazard state
bool hazardON = false;

void setup()
{
    pinMode(redLight, OUTPUT);
    pinMode(whiteLight, OUTPUT);
    pinMode(yellowLight, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    // constant rear lights always ON
    digitalWrite(whiteLight, HIGH);
    digitalWrite(redLight, HIGH);

    // button to GND, trigger when pressed
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, FALLING);
}

void loop()
{
    if (hazardON)
    {
        runHazardPattern();
    }
    else
    {
        digitalWrite(yellowLight, LOW);
    }
}

// -------------------------
// interrupt service routine
// -------------------------
void buttonPressed()
{
    if (hazardON)
    {
        hazardON = false;
    }
    else
    {
        hazardON = true;
    }
}

// double-flash pattern
void runHazardPattern()
{
    // the 'Tick'(Higher pitch), light on duration
    digitalWrite(yellowLight, HIGH);
    tone(buzzerPin, 700);
    delay(30);
    noTone(buzzerPin);
    delay(470);

    // the 'Tok' (Lower pitch), light off duration
    digitalWrite(yellowLight, LOW);
    tone(buzzerPin, 500);
    delay(30);
    noTone(buzzerPin);
    delay(470); // light off duration
}
