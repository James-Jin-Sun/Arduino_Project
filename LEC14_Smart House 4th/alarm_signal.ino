#include <Adafruit_NeoPixel.h>

int LED_PIN = 6;    // Connect to D (DIN)
int LED_COUNT = 12; // 12 LEDs on ring

// NEO_GRB   → color order used by WS2812 LEDs (Green, Red, Blue)
// NEO_KHZ800 → communication speed (800 kHz signal required by WS2812)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Create a NeoPixel LED strip object

int flamePin = 3;
bool flameValue;
int buzzerPin = 7;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(flamePin, INPUT);
    pinMode(buzzerPin, OUTPUT);
    strip.begin();
    strip.setBrightness(50); // Low brightness
    strip.show();            // send data to LED ring
}

void loop()
{
    // put your main code here, to run repeatedly:
    flameValue = digitalRead(flamePin);
    Serial.print("Flame Sensor Value: ");
    Serial.println(flameValue);
    if (flameValue == LOW)
    {
        Serial.println("Fire detected!");
        digitalWrite(buzzerPin, HIGH);
        setColor(255, 0, 0); // Red color for fire

    }
    else
    {
        Serial.println("No fire.");
        digitalWrite(buzzerPin, LOW);
        setColor(0, 0, 0); // Turn off LEDs
    }

    delay(1000);
}

void setColor(int r, int g, int b)
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
}