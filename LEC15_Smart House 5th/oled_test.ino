// Install Adafruit SSD1306 library from Library Manager
// Install Adafruit GFX library from Library Manager
// SDA = A4, SCL = A5

#include <Wire.h>
#include <Adafruit_GFX.h> // Graphics library
#include <Adafruit_SSD1306.h>  // OLED display library
// OLED display resolution
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C  // I2C address for OLED display

int tempValue = 25;
float humValue = 60.0;
bool fanState = true;

// Create an OLED display object
// Screen width, screen height, I2C communication, reset pin (-1 = not used)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
    // Initialize OLED display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
}

void loop()
{
    display.clearDisplay();
    display.setTextSize(2); // Bigger text → about 3-4 rows
    display.setTextColor(WHITE);

    // Row 1
    display.setCursor(0, 0);
    display.print("Temp:");
    display.print(tempValue);
    display.println(" C");

    // Row 2
    display.setCursor(0, 20);
    display.print("Hum:");
    display.print(humValue);
    display.println("%");

    // Row 3
    display.setCursor(0, 40);
    display.println("Fan ON");

    display.display();  // send all text to OLED
    delay(2000);  // wait for 2 seconds before refreshing the display
}