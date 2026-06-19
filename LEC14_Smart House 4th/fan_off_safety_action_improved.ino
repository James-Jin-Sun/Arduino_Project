#include <Adafruit_NeoPixel.h>

int LED_PIN = 6;    // Connect to D (DIN)
int LED_COUNT = 12; // 12 LEDs on ring

// NEO_GRB   → color order used by WS2812 LEDs (Green, Red, Blue)
// NEO_KHZ800 → communication speed (800 kHz signal required by WS2812)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Create a NeoPixel LED strip object

int flamePin = 3;
bool flameValue;
int buzeerPin = 7;

int motorPin_1 = 5; // DRV8833 IN1
int motorPin_2 = 9; // DRV8833 IN2

bool fireDetected = false; // Flag to indicate if fire is detected

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(flamePin, INPUT);
    pinMode(buzeerPin, OUTPUT);
    strip.begin();
    strip.setBrightness(50); // Low brightness
    strip.show();            // send data to LED ring
    pinMode(motorPin_1, OUTPUT);
    pinMode(motorPin_2, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(flamePin), fireSafety, FALLING);
}

void loop()
{
    // put your main code here, to run repeatedly:
    flameValue = digitalRead(flamePin);
    Serial.print("Flame Sensor Value: ");
    Serial.println(flameValue);
    if (fireDetected)
    {
        Serial.println("Fire detected!");
        digitalWrite(buzeerPin, HIGH);
        setColor(255, 0, 0); // Red color for fire

        analogWrite(motorPin_1, 0);
        analogWrite(motorPin_2, 0); // Turn off the fan
    }
    else
    {
        Serial.println("No fire.");
        digitalWrite(buzeerPin, LOW);
        setColor(0, 0, 0); // Turn off LEDs

        analogWrite(motorPin_1, 255);
        analogWrite(motorPin_2, 0); // Turn on the fan at full speed
    }

    delay(1000);
}

void fireSafety()
{
    fireDetected = true; // Set the flag to indicate that fire is detected
}

void setColor(int r, int g, int b)
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
}