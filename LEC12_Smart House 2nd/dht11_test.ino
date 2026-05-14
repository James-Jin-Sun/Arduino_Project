#include <DHT.h>

int dhtPin = 2;
int dhtType = DHT11;
DHT dht(dhtPin, dhtType);
float humi;
float temp;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    dht.begin();
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
    delay(2000);  // DHT11 sensor can only be read every 2 seconds
}