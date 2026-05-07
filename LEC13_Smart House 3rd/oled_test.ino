// Install Adafruit SSD1306 library from Library Manager
// Install Adafruit GFX library from Library Manager
// SDA = A4, SCL = A5

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();

    display.setTextSize(2); // Bigger text → about 3-4 rows
    display.setTextColor(WHITE);

    // Row 1
    display.setCursor(0, 0);
    display.println("Temp:25C");

    // Row 2
    display.setCursor(0, 20);
    display.println("Hum:60%");

    // Row 3
    display.setCursor(0, 40);
    display.println("Fan ON");

    display.display();
}

void loop()
{
}