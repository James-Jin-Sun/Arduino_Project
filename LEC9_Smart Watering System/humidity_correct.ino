int shsPin = A0;
float shsVal;
float humidity;

void setup()
{
    // put your setup code here, to run once:
    pinMode(shsPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    shsVal = analogRead(shsPin);
    humidity = (shsVal / 1023) * 100;
    Serial.print("Soil humidity sensor reading:");
    Serial.println(shsVal);
    Serial.print("Humidity:");
    Serial.println(humidity);
    delay(100);
}