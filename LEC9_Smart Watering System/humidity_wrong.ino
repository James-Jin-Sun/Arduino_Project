int shsPin = A0;
int shsVal;
float humidity;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    shsVal = analogRead(shsPin);
    humidity = (shsVal / 1023) * 100;
    Serial.print("Reading of Soil Humidity Sensor:");
    Serial.println(shsVal);
    Serial.print("Humidity:");
    Serial.println(humidity);
    delay(100);
}