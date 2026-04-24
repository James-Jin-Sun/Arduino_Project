int shsPin = A0;
float shsVal;
float humidity;
int waterpPin = 8; // water pump pin
int soilHumThs = 60;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(shsPin, INPUT);
    pinMode(waterpPin, OUTPUT);
    Serial.print("Smart Watering System Ready!");
}

void loop()
{
    // put your main code here, to run repeatedly:
    shsVal = analogRead(shsPin);
    humidity = (shsVal / 1023) * 100;
    Serial.print("Humidity:");
    Serial.print(humidity);
    Serial.println("%");

    if (humidity < soilHumThs)
    {
        digitalWrite(waterpPin, HIGH);
        delay(5000);
        digitalWrite(waterpPin, LOW);
        delay(3000); // wait for soil to absorb water
    }
    else
    {
        digitalWrite(waterpPin, LOW);
    }
}

void water_pump_test()
{
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