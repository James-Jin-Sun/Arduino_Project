#include <Wire.h>              // use Wire library
#include <LiquidCrystal_I2C.h> // use LiquidCrystal(LCD) with I2C library

int shsPin = A0;
float shsVal;
float humidity;
int waterpPin = 8;                  // water pump pin
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(shsPin, INPUT);
    pinMode(waterpPin, OUTPUT);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Smart Watering");
    lcd.setCursor(0, 1);
    lcd.print("System Ready!");
    delay(2000);
    lcd.clear();
}

void loop()
{
    // put your main code here, to run repeatedly:
}

void testSHS()
{
    shsVal = analogRead(shsPin);
    humidity = (shsVal / 1023) * 100;
    Serial.print("Soil humidity sensor reading:");
    Serial.println(shsVal);
    Serial.print("Humidity:");
    Serial.println(humidity);
    delay(100);
}

void watering()
{
    digitalWrite(waterpPin, HIGH);
    delay(5000);
    digitalWrite(waterpPin, LOW);
    delay(1000);
}