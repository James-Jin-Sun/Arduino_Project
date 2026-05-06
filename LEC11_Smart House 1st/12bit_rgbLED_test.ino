#include <Adafruit_NeoPixel.h>

int LED_PIN = 6;    // Connect to D (DIN)
int LED_COUNT = 12; // 12 LEDs on ring

// NEO_GRB   → color order used by WS2812 LEDs (Green, Red, Blue)
// NEO_KHZ800 → communication speed (800 kHz signal required by WS2812)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Create a NeoPixel LED strip object

void setup()
{
    // put your setup code here, to run once:
    strip.begin();
    strip.setBrightness(100); // Medium
    strip.show();             // Turn OFF all LEDs
}

void loop()
{
    // put your main code here, to run repeatedly:
    // 🔴 RED
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(800);

    // 🟢 GREEN
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
    }
    strip.show();
    delay(800);

    // 🔵 BLUE
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
    strip.show();
    delay(800);

    // ⚪ WHITE
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
    strip.show();
    delay(800);
    
    // ⚫ OFF
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(800);
}