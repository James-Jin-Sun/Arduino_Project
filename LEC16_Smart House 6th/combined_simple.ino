// ---------- Libraries  ----------
#include <Adafruit_NeoPixel.h>    // 12 bit RGB LED library
#include <DHT.h>               // DHT11 temp & humi sensor library
#include <Servo.h>            // use Servo library
#include <Wire.h>             // I2C communication library
#include <Adafruit_GFX.h>     // Graphics library
#include <Adafruit_SSD1306.h> // OLED display library

// ---------- Pin Def., Objects & Variables ----------
// 12 bit RGB LED + light sensor
int LED_PIN = 6; // Connect to D (DIN)
int LED_COUNT = 12; // 12 LEDs on ring
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Create a NeoPixel LED strip object
int lsPin = A0; // set light sensor=A0
int lsValue;    // light sensor value
int lsThs = 150;

// DHT11 temp & humi sensor + DC motor
int dhtPin = 2; // DHT11 data pin
int dhtType = DHT11;
DHT dht(dhtPin, dhtType);
float humi;
float temp;
int motorPin_1 = 5; // DRV8833 IN1
int motorPin_2 = 9; // DRV8833 IN2
int medWarm = 25;   // replace tempThs_1 with medWarm
int veryWarm = 30;  // replace tempThs_2 with veryWarm

// rain sensor + servo motor
int rainPin = A1;
int rainValue;
int lightRainThs = 700; // light rain threshold
int heavyRainThs = 400; // heavy rain threshold
int servoPin = 10;
int winClosDeg = 0;
int winHalfDeg = 90;
int winOpenDeg = 180;
Servo windowServo;

// flame sensor + buzzer
int flamePin = 3;
bool flameValue;
int buzzerPin = 7;
bool fireDetected = false;  // Flag to indicate if fire is detected
int countFire = 0;          // Counter for flame sensor readings
int countNoFire = 0;        // Counter for no fire readings
bool fireTriggered = false; // Flag to indicate if fire safety action has been triggered

// OLED display
int SCREEN_WIDTH = 128;
int SCREEN_HEIGHT = 64;
int OLED_ADDR = 0x3C; // I2C address for OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
bool oledReady = false;


// ---------- Setup ----------
void setup()
{
    // put your setup code here, to run once:
    // 12 bit RGB LED + light sensor
    strip.begin();
    strip.setBrightness(50); // Low brightness
    strip.show();            // send data to LED ring
    pinMode(lsPin, INPUT);

    // DHT11 temp & humi sensor + DC motor
    dht.begin();
    pinMode(motorPin_1, OUTPUT);
    pinMode(motorPin_2, OUTPUT);

    // rain sensor + servo motor
    windowServo.attach(servoPin); // attaches servo to pin 10

    // flame sensor + buzzer
    pinMode(flamePin, INPUT);
    pinMode(buzzerPin, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(flamePin), fireSafety, FALLING);

    // OLED display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);

    // serial monitor for debugging
    Serial.begin(9600);
}

// ---------- Loop ----------
void loop()
{
    // put your main code here, to run repeatedly:
    checkFire();
    if (fireDetected)
    {
        handleFireDetected();
    }
    else
    {
        handleSmartLighting();
        updateTempHumi();
        handleAutoFanCooling();
        handleRainResponse();
        handleDisplay();
    }
}

// ---------- Functions ----------
// --- Smart Lighting ---
void handleSmartLighting()
{
    lsValue = analogRead(lsPin);
    Serial.print("Light Value: ");
    Serial.println(lsValue);
    if (lsValue < lsThs)
    {
        rainbow();
    }
    else
    {
        setColor(0, 0, 0);
    }
    delay(500);
}

void rainbow()
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

// --- Auto Fan Cooling ---
void updateTempHumi()
{
    humi = dht.readHumidity();
    temp = dht.readTemperature(); // Celsius
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print("°C, Humidity: ");
    Serial.print(humi);
    Serial.println("%");
    delay(2000); // DHT11 sensor can only be read every 2 seconds
}

void handleAutoFanCooling()
{
    if (temp < medWarm)
    {
        analogWrite(motorPin_1, 0);
        analogWrite(motorPin_2, 0); // stop motor: both inputs LOW
        Serial.println("Fan OFF");
    }
    else if (temp >= medWarm && temp < veryWarm)
    {
        analogWrite(motorPin_1, 153);
        analogWrite(motorPin_2, 0); // half speed cooling fan
        Serial.println("Cooling Mode - Med");
    }
    else
    {
        analogWrite(motorPin_1, 255);
        analogWrite(motorPin_2, 0); // full speed cooling fan
        Serial.println("Cooling Mode - High");
    }
}

// --- Rain Response ---
void handleRainResponse()
{
    rainValue = analogRead(rainPin);
    Serial.print("Rain Value: ");
    Serial.println(rainValue);

    if (rainValue > lightRainThs)
    {
        // No rain
        windowServo.write(winOpenDeg); // Open the window
        Serial.println("No Rain. Keeping the window open.");
    }
    else if (rainValue <= lightRainThs && rainValue > heavyRainThs)
    {
        // Light rain
        windowServo.write(winHalfDeg); // Partially open the window
        Serial.println("Light Rain Detected! Partially opening the window.");
    }
    else // rainValue <= heavyRainThs
    {
        // Heavy rain
        windowServo.write(winClosDeg); // Close the window
        Serial.println("Heavy Rain Detected! Closing the window.");
    }
    delay(500);
}

// --- Fire Safety ---
void handleFireDetected()
{
    Serial.println("Fire detected!");
    digitalWrite(buzzerPin, HIGH);
    setColor(255, 0, 0); // Red color for fire

    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 0); // Turn off the fan
}

void checkFire()
{
    countFire = 0;   // Reset the counter for each loop iteration
    countNoFire = 0; // Reset the no fire counter for each loop iteration

    // Read the flame sensor value 5 consecutive times
    for (int i = 0; i < 5; i++)
    {
        flameValue = digitalRead(flamePin);
        if (flameValue == LOW)
        {
            countFire += 1;
        }
        else
        {
            countNoFire += 1;
        }
        Serial.print("Flame Sensor Value: ");
        Serial.print(flameValue);
        Serial.print(" | Count Fire: ");
        Serial.print(countFire);
        Serial.print(" | Count No Fire: ");
        Serial.println(countNoFire);
        delay(200); // short delay between readings
    }
    // check if the flame sensor value is LOW for 5 consecutive readings
    if (countNoFire == 5)
    {
        fireDetected = false;
    }
    if (fireTriggered && countFire >= 3)
    {
        fireDetected = true;
        fireTriggered = false; // Reset the flag after taking action
    }
}

void fireSafety()
{
    fireTriggered = true; // Set the flag to indicate that fire safety action has been triggered
}

// OLED Display
void handleDisplay()
{
    if (!oledReady)
    {
        return;
    }

    display.clearDisplay();
    display.setTextSize(2); // Bigger text → about 3-4 rows
    display.setTextColor(WHITE);

    // Row 1
    display.setCursor(0, 0);
    display.print("Temp:");
    display.print(temp, 1); // print temperature with 0 decimal places
    display.println("C");

    // Row 2
    display.setCursor(0, 20);
    display.print("Hum:");
    display.print(humi, 1); // print temperature with no decimal places
    display.println("%");

    display.display(); // send all text to OLED
}