int reedSwitch = 4;
bool reed_switch_value;
int redLED = 2;
int buzzerPin = 3;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(reedSwitch, INPUT);
    pinMode(redLED, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    reed_switch_value = digitalRead(reedSwitch);
    if (reed_switch_value == LOW)
    {
        digitalWrite(redLED, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(200);

        digitalWrite(buzzerPin, LOW);
        delay(300);

        digitalWrite(redLED, LOW);
        delay(500);
    }
}
