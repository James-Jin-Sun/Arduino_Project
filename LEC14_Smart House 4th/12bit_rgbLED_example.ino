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
    strip.setBrightness(50); // Low Brightness
    strip.show();            // Turn OFF all LEDs
}

void loop()
{
    // put your main code here, to run repeatedly:
    // ⚪ WHITE
    setColor(255, 255, 255);
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