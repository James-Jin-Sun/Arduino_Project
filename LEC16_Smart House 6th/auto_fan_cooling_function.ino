#include <DHT.h>

int dhtPin = 2;
int dhtType = DHT11;
DHT dht(dhtPin, dhtType);
float humi;
float temp;
int motorPin_1 = 5; // DRV8833 IN1
int motorPin_2 = 9; // DRV8833 IN2

int medWarm = 25;  // replace tempThs_1 with medWarm
int veryWarm = 30; // replace tempThs_2 with veryWarm

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
    handleAutoFanCooling();
}

void handleAutoFanCooling()
{
    humi = dht.readHumidity();
    temp = dht.readTemperature(); // Celsius
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print("°C, Humidity: ");
    Serial.print(humi);
    Serial.println("%");
    if (temp < medWarm)
    {
        analogWrite(motorPin_1, 0);
        analogWrite(motorPin_2, 0); // stop motor: both inputs LOW
        Serial.println("Fan OFF");
    }
    else if (temp >= medWarm && temp < veryWarm)
    {
        analogWrite(motorPin_1, 153);
        analogWrite(motorPin_2, 0);  // half speed cooling fan
        Serial.println("Cooling Mode - Med");
    }
    else {
        analogWrite(motorPin_1, 255);
        analogWrite(motorPin_2, 0);  // full speed cooling fan
        Serial.println("Cooling Mode - High");
    }
    delay(2000);  // DHT11 sensor can only be read every 2 seconds
}