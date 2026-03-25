int reedSwitch = 4;
bool reed_switch_value;
int redLED = 2;
int buzzerPin = 3;
int soundSensor = A0;
int sound_sensor_value;
int soundTh = 50;
int pirSensor = 5;
bool pir_sensor_value;
int greenLED = 6;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(reedSwitch, INPUT);
    pinMode(redLED, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(soundSensor, INPUT);
    pinMode(pirSensor, INPUT);
    pinMode(greenLED, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    reed_switch_value = digitalRead(reedSwitch);  // reed - L1
    sound_sensor_value = analogRead(soundSensor); // sound - L2
    pir_sensor_value = digitalRead(pirSensor);    // pir - L3
    if (pir_sensor_value == HIGH)
    {
        pirL3();
    }
    else if (sound_sensor_value >= soundTh)
    {
        soundL2();
    }
    else if (reed_switch_value == HIGH)
    {
        reedL1();
    }
    else
    {
        safeState();
    }
}

void reedL1()
{
    digitalWrite(greenLED, LOW); // intrusion detected
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(200);

    digitalWrite(buzzerPin, LOW);
    delay(300);

    digitalWrite(redLED, LOW);
    delay(500);
}

void soundL2()
{
    digitalWrite(greenLED, LOW); // intrusion detected
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(150);

    digitalWrite(redLED, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(150);
}

void pirL3()
{
    digitalWrite(greenLED, LOW); // intrusion detected
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzerPin, HIGH);
}

void safeState()
{
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);    // red LED off
    digitalWrite(buzzerPin, LOW); // buzzer off
}