// ---------- Libraries  ----------
#include <Adafruit_NeoPixel.h> // 12 bit RGB LED library
#include <DHT.h>               // DHT11 temp & humi sensor library

// ---------- Pin Def., Objects & Variables ----------
// 12 bit RGB LED + light sensor
int LED_PIN = 8;                                                   // Connect to D (DIN)
int LED_COUNT = 12;                                                // 12 LEDs on ring
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Create a NeoPixel LED strip object
int lsPin = A0;                                                    // set light sensor=A0
int lsValue;                                                       // light sensor value
int lsThs = 150;

// DHT11 temp & humi sensor + DC motor
int dhtPin = 2; // DHT11 data pin
int dhtType = DHT11;
DHT dht(dhtPin, dhtType);
float humi;
float temp;
int motorPin_1 = 5; // DRV8833 IN1
int motorPin_2 = 6; // DRV8833 IN2
int medWarm = 22;   // replace tempThs_1 with medWarm
int veryWarm = 24;  // replace tempThs_2 with veryWarm

// ---------- Setup ----------
void setup()
{
    // put your setup code here, to run once:
    // serial monitor for debugging
    Serial.begin(9600);

    // 12 bit RGB LED + light sensor
    strip.begin();
    strip.setBrightness(50); // Low brightness
    strip.show();            // send data to LED ring
    pinMode(lsPin, INPUT);

    // DHT11 temp & humi sensor + DC motor
    dht.begin();
    pinMode(motorPin_1, OUTPUT);
    pinMode(motorPin_2, OUTPUT);
}

// ---------- Loop ----------
void loop()
{
    // put your main code here, to run repeatedly:
    handleSmartLighting();
    updateTempHumi();
    handleAutoFanCooling();
}

// ---------- Functions ----------
// --- Smart Lighting ---
void handleSmartLighting()
{
    lsValue = analogRead(lsPin);
    Serial.print("Light Value: ");
    Serial.println(lsValue);
    if (lsValue < lsThs)
    {
        rainbow();
    }
    else
    {
        setColor(0, 0, 0);
    }
    delay(500);
}

void rainbow()
{
    // 🔴 RED
    setColor(255, 0, 0);
    delay(800);

    // 🟡 Yellow
    setColor(255, 255, 0);
    delay(800);

    // 🟠 Orange
    setColor(255, 100, 0);
    delay(800);

    // 🟢 GREEN
    setColor(0, 255, 0);
    delay(800);

    // 🔵 BLUE
    setColor(0, 0, 255);
    delay(800);

    // 🔷 Indigo
    setColor(75, 0, 130);
    delay(800);

    // 🟣 Violet
    setColor(148, 0, 211);
    delay(800);

    // ⚫ OFF
    setColor(0, 0, 0);
    delay(800);
}

void setColor(int r, int g, int b)
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
}

// --- Auto Fan Cooling ---
void updateTempHumi()
{
    humi = dht.readHumidity();
    temp = dht.readTemperature(); // Celsius
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print("°C, Humidity: ");
    Serial.print(humi);
    Serial.println("%");
    delay(2000); // DHT11 sensor can only be read every 2 seconds
}

void handleAutoFanCooling()
{
    if (temp < medWarm)
    {
        fanOff();
    }
    else if (temp >= medWarm && temp < veryWarm)
    {
        analogWrite(motorPin_1, 153);
        analogWrite(motorPin_2, 0); // half speed cooling fan
        Serial.println("Cooling Mode - Med");
    }
    else
    {
        analogWrite(motorPin_1, 255);
        analogWrite(motorPin_2, 0); // full speed cooling fan
        Serial.println("Cooling Mode - High");
    }
}

void fanOff()
{
    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 0); // stop motor: both inputs LOW
    Serial.println("Fan OFF");
}