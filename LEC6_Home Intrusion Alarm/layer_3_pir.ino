int reedSwitch = 4;
bool reed_switch_value;
int redLED = 2;
int buzzerPin = 3;
int soundSensor = A0;
int sound_sensor_value;
int soundTh = 50;
int pirSensor = 5;
bool pir_sensor_value;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(reedSwitch, INPUT);
    pinMode(redLED, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(soundSensor, INPUT);
    pinMode(pirSensor, INPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    pir_sensor_value = digitalRead(pirSensor);
    if (pir_sensor_value == HIGH)
    {
        digitalWrite(redLED, HIGH);
        digitalWrite(buzzerPin, HIGH);
    }
    else
    {
        digitalWrite(redLED, LOW);
        digitalWrite(buzzerPin, LOW);
    }
}

void reedL1()
{
    reed_switch_value = digitalRead(reedSwitch);
    if (reed_switch_value == HIGH)
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

void soundL2()
{
    sound_sensor_value = analogRead(soundSensor);
    if (sound_sensor_value >= soundTh)
    {
        digitalWrite(redLED, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(150);

        digitalWrite(redLED, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(150);
    }
}