#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>     // Graphics library
#include <Adafruit_SSD1306.h> // OLED display library
// OLED display resolution
int SCREEN_WIDTH = 128;
int SCREEN_HEIGHT = 64;
int OLED_ADDR = 0x3C; // I2C address for OLED display

// Create an OLED display object
// Screen width, screen height, I2C communication, reset pin (-1 = not used)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int dhtPin = 2;
int dhtType = DHT11;
DHT dht(dhtPin, dhtType);
float humi;
float temp;

void setup()
{
    // put your setup code here, to run once:
    // Create an OLED display object
    // Initialize OLED display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    dht.begin();
}

void loop()
{
    // put your main code here, to run repeatedly:
    humi = dht.readHumidity();
    temp = dht.readTemperature(); // Celsius
    handleDisplay();
}

void handleDisplay()
{
    display.clearDisplay();
    display.setTextSize(2); // Bigger text → about 3-4 rows
    display.setTextColor(WHITE);

    // Row 1
    display.setCursor(0, 0);
    display.print("Temp:");
    display.print(temp, 1); // print temperature with 1 decimal places
    display.println("C");

    // Row 2
    display.setCursor(0, 20);
    display.print("Hum:");
    display.print(humi, 1); // print temperature with 1 decimal places
    display.println("%");

    display.display(); // send all text to OLED
}
