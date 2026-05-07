#include <DHT.h>

int dhtPin = 2;
int dhtType = DHT11;
DHT dht(dhtPin, dhtType);
float humi;
float temp;
int motorPin = 5;
int tempThs_1 = 25;
int tempThs_2 = 30;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    dht.begin();
    pinMode(motorPin, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    humi = dht.readHumidity();
    temp = dht.readTemperature(); // Celsius
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print("°C, Humidity: ");
    Serial.print(humi);
    Serial.println("%");
    if (temp < tempThs_1)
    {
        analogWrite(motorPin, 0);
        Serial.println("Fan OFF");
    }
    else if (temp < tempThs_2)
    {
        analogWrite(motorPin, 153);
        Serial.println("Fan ON - Med");
    }
    else
    {
        analogWrite(motorPin, 255);
        Serial.println("Fan ON - High");
    }
    delay(2000);
}