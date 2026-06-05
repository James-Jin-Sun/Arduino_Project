int flamePin = 3;
bool flameValue;
int buzeerPin = 7;
int redLEDPin = 8;

int motorPin_1 = 5; // DRV8833 IN1
int motorPin_2 = 9; // DRV8833 IN2

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(flamePin, INPUT);
    pinMode(buzeerPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);
    pinMode(motorPin_1, OUTPUT);
    pinMode(motorPin_2, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    flameValue = digitalRead(flamePin);
    Serial.print("Flame Sensor Value: ");
    Serial.println(flameValue);
    if (flameValue == LOW)
    {
        Serial.println("Fire detected!");
        digitalWrite(buzeerPin, HIGH);
        digitalWrite(redLEDPin, HIGH);
        
        digitalWrite(motorPin_1, LOW);
        digitalWrite(motorPin_2, LOW);
    }
    else
    {
        Serial.println("No fire.");
        digitalWrite(buzeerPin, LOW);
        digitalWrite(redLEDPin, LOW);
    }

    delay(500);
}