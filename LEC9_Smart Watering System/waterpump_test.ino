int shsPin = A0;
float shsVal;
float humidity;
int waterpPin = 8; // water pump pin

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(shsPin, INPUT);
    pinMode(waterpPin, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    digitalWrite(waterpPin, HIGH);
    delay(5000);
    digitalWrite(waterpPin, LOW);
    delay(1000);
}

void testSHS()
{
    shsVal = analogRead(shsPin);
    humidity = (shsVal / 1023) * 100;
    Serial.print("Soil humidity sensor reading:");
    Serial.println(shsVal);
    Serial.print("Humidity:");
    Serial.println(humidity);
    Serial.println("%");
    delay(100);
}