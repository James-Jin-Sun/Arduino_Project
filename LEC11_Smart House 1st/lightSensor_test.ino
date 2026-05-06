#include <Adafruit_NeoPixel.h>

int LED_PIN = 6;    // Connect to D (DIN)
int LED_COUNT = 12; // 12 LEDs on ring

// NEO_GRB   → color order used by WS2812 LEDs (Green, Red, Blue)
// NEO_KHZ800 → communication speed (800 kHz signal required by WS2812)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Create a NeoPixel LED strip object

int lsPin = A0; // set light sensor=A0
int lsValue;    // light sensor value

void setup()
{
    // put your setup code here, to run once:
    strip.begin();
    strip.setBrightness(50); // Low brightness
    strip.show();            // Turn OFF all LEDs
    pinMode(lsPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    lsValue = analogRead(lsPin);
    Serial.print("Light Value: ");
    Serial.println(lsValue);
    delay(500);
}

void ranbow()
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