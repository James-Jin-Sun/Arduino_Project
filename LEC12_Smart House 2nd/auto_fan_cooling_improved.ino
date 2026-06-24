#include <DHT.h>

int dhtPin = 2;
int dhtType = DHT11;
DHT dht(dhtPin, dhtType);
float humi;
float temp;
int motorPin_1 = 5; // DRV8833 IN1
int motorPin_2 = 9; // DRV8833 IN2

int tempThs_1 = 25;  // medium warm
int tempThs_2 = 30;  // very warm

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    dht.begin();
    pinMode(motorPin_1, OUTPUT);
    pinMode(motorPin_2, OUTPUT);
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
        analogWrite(motorPin_1, 0);
        analogWrite(motorPin_2, 0); // stop motor: both inputs LOW
        Serial.println("Fan OFF");
    }
    else if (temp >= tempThs_1 && temp < tempThs_2)
    {
        analogWrite(motorPin_1, 153);
        analogWrite(motorPin_2, 0);  // hlaf speed cooling fan
        Serial.println("Cooling Mode - Med");
    }
    else {
        analogWrite(motorPin_1, 255);
        analogWrite(motorPin_2, 0);  // full speed cooling fan
        Serial.println("Cooling Mode - High");
    }
    delay(2000);  // DHT11 sensor can only be read every 2 seconds
}