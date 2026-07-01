// ---------- Libraries  ----------
#include <Adafruit_NeoPixel.h> // 12 bit RGB LED library
#include <DHT.h>               // DHT11 temp & humi sensor library
#include <Servo.h>             // use Servo library
#include <Wire.h>              // I2C communication library
#include <Adafruit_GFX.h>      // Graphics library
#include <Adafruit_SSD1306.h>  // OLED display library

// ---------- Pin Def., Objects & Variables ----------
// 12 bit RGB LED + light sensor
#define LED_PIN 8                                                  // Connect to D (DIN)
#define LED_COUNT 12                                               // 12 LEDs on ring
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Create a NeoPixel LED strip object
#define lsPin A0                                                   // set light sensor=A0
int lsValue;                                                       // light sensor value
#define lsThs 150

// DHT11 temp & humi sensor + DC motor
#define dhtPin 2 // DHT11 data pin
#define dhtType DHT11
DHT dht(dhtPin, dhtType);
float humi;
float temp;
#define motorPin_1 5 // DRV8833 IN1
#define motorPin_2 6 // DRV8833 IN2
#define medWarm 22   // replace tempThs_1 with medWarm
#define veryWarm 24  // replace tempThs_2 with veryWarm

// rain sensor + servo motor
#define rainPin A1
int rainValue;
#define lightRainThs 700 // light rain threshold
#define heavyRainThs 400 // heavy rain threshold
#define servoPin 10
#define winClosDeg 0
#define winHalfDeg 90
#define winOpenDeg 180
Servo windowServo;

// flame sensor + buzzer
#define flamePin 3
bool flameValue;
#define buzzerPin 7
bool fireDetected = false;  // Flag to indicate if fire is detected
byte countFire = 0;         // Counter for flame sensor readings
byte countNoFire = 0;       // Counter for no fire readings
bool fireTriggered = false; // Flag to indicate if fire safety action has been triggered

// OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C // I2C address for OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
bool oledReady = false;

bool initOLED()
{
    Wire.begin();

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    {
        Serial.println("OLED init failed. Check wiring/address/ram.");
        return false;
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("OLED Ready");
    display.display();
    delay(800);
    return true;
}

// ---------- Setup ----------
void setup()
{
    // put your setup code here, to run once:
    // serial monitor for debugging
    Serial.begin(9600);

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
    oledReady = initOLED();
}

// ---------- Loop ----------
void loop()
{
    // put your main code here, to run repeatedly:
    checkFire();
    if (fireDetected)
    {
        handleFireDetected();
        updateTempHumi();
        handleDisplay();
    }
    else
    {
        digitalWrite(buzzerPin, LOW); // Turn off buzzer
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
    checkFire();
    if (fireDetected)
    {
        return;
    }

    lsValue = analogRead(lsPin);
    Serial.print(F("Light Value: "));
    Serial.println(lsValue);
    if (lsValue < lsThs)
    {
        rainbow();
    }
    else
    {
        setColor(0, 0, 0);
    }
    // delay(500);
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
    // delay(800);
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
    checkFire();
    if (fireDetected)
    {
        return;
    }

    humi = dht.readHumidity();
    temp = dht.readTemperature(); // Celsius
    Serial.print(F("Temperature: "));
    Serial.print(temp);
    Serial.print(F("°C, Humidity: "));
    Serial.print(humi);
    Serial.println(F("%"));
    delay(2000); // DHT11 sensor can only be read every 2 seconds
}

void handleAutoFanCooling()
{
    checkFire();
    if (fireDetected)
    {
        return;
    }

    if (temp < medWarm)
    {
        fanOff();
    }
    else if (temp >= medWarm && temp < veryWarm)
    {
        analogWrite(motorPin_1, 153);
        analogWrite(motorPin_2, 0); // half speed cooling fan
        Serial.println(F("Cooling Mode - Med"));
    }
    else
    {
        analogWrite(motorPin_1, 255);
        analogWrite(motorPin_2, 0); // full speed cooling fan
        Serial.println(F("Cooling Mode - High"));
    }
}

void fanOff()
{
    analogWrite(motorPin_1, 0);
    analogWrite(motorPin_2, 0); // stop motor: both inputs LOW
    Serial.println(F("Fan OFF"));
}

// --- Rain Response ---
void handleRainResponse()
{
    checkFire();
    if (fireDetected)
    {
        return;
    }

    rainValue = analogRead(rainPin);
    Serial.print(F("Rain Value: "));
    Serial.println(rainValue);

    if (rainValue > lightRainThs)
    {
        // No rain
        windowServo.write(winOpenDeg); // Open the window
        Serial.println(F("No Rain. Keeping the window open."));
    }
    else if (rainValue <= lightRainThs && rainValue > heavyRainThs)
    {
        // Light rain
        windowServo.write(winHalfDeg); // Partially open the window
        Serial.println(F("Light Rain Detected! Partially opening the window."));
    }
    else // rainValue <= heavyRainThs
    {
        // Heavy rain
        windowServo.write(winClosDeg); // Close the window
        Serial.println(F("Heavy Rain Detected! Closing the window."));
    }
    // delay(500);
}

// --- Fire Safety ---
void handleFireDetected()
{
    Serial.println(F("Fire detected!"));
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
        Serial.print(F("Flame Sensor Value: "));
        Serial.print(flameValue);
        Serial.print(F(" | Count Fire: "));
        Serial.print(countFire);
        Serial.print(F(" | Count No Fire: "));
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
    checkFire();
    if (fireDetected)
    {
        return;
    }

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
    display.print(temp, 1); // print temperature with 1 decimal places
    display.println("C");

    // Row 2
    display.setCursor(0, 20);
    display.print("Hum:");
    display.print(humi, 1); // print humidity with 1 decimal places
    display.println("%");

    display.display(); // send all text to OLED
}