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
    strip.show();            // send data to LED ring
}

void loop()
{
    // put your setup code here, to run once:
    // ⚪ WHITE
    strip.setPixelColor(0, strip.Color(255, 255, 255));  // Turn ON LED #0 (1st LED)
    strip.setPixelColor(1, strip.Color(255, 255, 255));  // Turn ON LED #1 (2nd LED)
    strip.setPixelColor(2, strip.Color(255, 255, 255));  // Turn ON LED #2 (3rd LED)
    strip.setPixelColor(3, strip.Color(255, 255, 255));  // Turn ON LED #3 (4th LED)
    strip.setPixelColor(4, strip.Color(255, 255, 255));  // Turn ON LED #4 (5th LED)
    strip.setPixelColor(5, strip.Color(255, 255, 255));  // Turn ON LED #5 (6th LED)
    strip.setPixelColor(6, strip.Color(255, 255, 255));  // Turn ON LED #6 (7th LED)
    strip.setPixelColor(7, strip.Color(255, 255, 255));  // Turn ON LED #7 (8th LED)
    strip.setPixelColor(8, strip.Color(255, 255, 255));  // Turn ON LED #8 (9th LED)
    strip.setPixelColor(9, strip.Color(255, 255, 255));  // Turn ON LED #9 (10th LED)
    strip.setPixelColor(10, strip.Color(255, 255, 255)); // Turn ON LED #10 (11th LED)
    strip.setPixelColor(11, strip.Color(255, 255, 255)); // Turn ON LED #11 (12th LED)
    strip.show();
    delay(800);
}