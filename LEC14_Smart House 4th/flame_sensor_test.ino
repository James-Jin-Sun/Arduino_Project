int flamePin = 3;
bool flameValue;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(flamePin, INPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    flameValue = digitalRead(flamePin);
    Serial.print("Flame Sensor Value: ");
    Serial.println(flameValue);
    delay(1000);
}