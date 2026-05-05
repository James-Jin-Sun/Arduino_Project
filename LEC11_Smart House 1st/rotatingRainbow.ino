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
    strip.setBrightness(50); // Low brightness
    strip.show();             // Turn OFF all LEDs
}

void loop()
{
    // put your main code here, to run repeatedly:
    for (int j = 0; j < 256; j++)
    { // cycle through colors
        for (int i = 0; i < LED_COUNT; i++)
        {
            strip.setPixelColor(i, Wheel((i * 256 / LED_COUNT + j) & 255));
        }
        strip.show();
        delay(30); // speed (lower = faster)
    }
}

uint32_t Wheel(byte pos)
{
    pos = 255 - pos;
    if (pos < 85)
    {
        return strip.Color(255 - pos * 3, 0, pos * 3);
    }
    else if (pos < 170)
    {
        pos -= 85;
        return strip.Color(0, pos * 3, 255 - pos * 3);
    }
    else
    {
        pos -= 170;
        return strip.Color(pos * 3, 255 - pos * 3, 0);
    }
}