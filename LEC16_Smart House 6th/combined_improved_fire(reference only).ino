// ---------- Libraries  ----------
#include <Adafruit_NeoPixel.h> // 12 bit RGB LED library
#include <DHT.h>               // DHT11 temp & humi sensor library
#include <Servo.h>             // use Servo library
#include <Wire.h>              // I2C communication library
#include <Adafruit_GFX.h>      // Graphics library
#include <Adafruit_SSD1306.h>  // OLED display library

// ---------- Pin Def., Objects & Variables ----------
// 12 bit RGB LED + light sensor
#define LED_PIN 6                                                  // Connect to D (DIN)
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
#define motorPin_2 9 // DRV8833 IN2
#define medWarm 25   // replace tempThs_1 with medWarm
#define veryWarm 30  // replace tempThs_2 with veryWarm

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
byte countFire = 0;          // Counter for flame sensor readings
byte countNoFire = 0;        // Counter for no fire readings
volatile bool fireEdgeDetected = false;

// OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C // I2C address for OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
bool oledReady = false;

bool initOLED()
{
    Wire.begin();

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    {
        Serial.println(F("OLED init failed. Check wiring/address/ram."));
        return false;
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(F("OLED Ready"));
    display.display();
    delay(800);
    return true;
}

void fireSafetyISR()
{
    // ISR must stay tiny: only capture the edge event.
    fireEdgeDetected = true;
}

bool confirmFireBurst(byte samples = 7, byte requiredLow = 5, byte gapMs = 10)
{
    byte lowCount = 0;
    for (byte i = 0; i < samples; i++)
    {
        if (digitalRead(flamePin) == LOW)
        {
            lowCount++;
            if (lowCount >= requiredLow)
            {
                return true;
            }
        }
        delay(gapMs);
    }
    return false;
}

void processFireDetection()
{
    if (fireDetected)
    {
        return;
    }

    bool edgePending;
    noInterrupts();
    edgePending = fireEdgeDetected;
    fireEdgeDetected = false;
    interrupts();

    // Immediate confirm either on captured edge or active LOW level.
    if (edgePending || digitalRead(flamePin) == LOW)
    {
        if (confirmFireBurst())
        {
            fireDetected = true;
            Serial.println(F("Fire confirmed by burst sampling."));
        }
    }
}

bool interruptibleDelay(unsigned long totalMs)
{
    unsigned long start = millis();
    while (millis() - start < totalMs)
    {
        processFireDetection();
        if (fireDetected)
        {
            return true;
        }
        delay(1);
    }
    return false;
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
    pinMode(flamePin, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(flamePin), fireSafetyISR, FALLING);

    // OLED display
    oledReady = initOLED();
}

// ---------- Loop ----------
void loop()
{
    // put your main code here, to run repeatedly:
    processFireDetection();
    if (fireDetected)
    {
        handleFireDetected();
        handleDisplay();
    }
    else
    {
        digitalWrite(buzzerPin, LOW);
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
    processFireDetection();
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
    interruptibleDelay(500);
}

void rainbow()
{
    // 🔴 RED
    setColor(255, 0, 0);
    if (interruptibleDelay(800))
        return;

    // 🟡 Yellow
    setColor(255, 255, 0);
    if (interruptibleDelay(800))
        return;

    // 🟠 Orange
    setColor(255, 100, 0);
    if (interruptibleDelay(800))
        return;

    // 🟢 GREEN
    setColor(0, 255, 0);
    if (interruptibleDelay(800))
        return;

    // 🔵 BLUE
    setColor(0, 0, 255);
    if (interruptibleDelay(800))
        return;

    // 🔷 Indigo
    setColor(75, 0, 130);
    if (interruptibleDelay(800))
        return;

    // 🟣 Violet
    setColor(148, 0, 211);
    if (interruptibleDelay(800))
        return;

    // ⚫ OFF
    setColor(0, 0, 0);
    interruptibleDelay(800);
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
    processFireDetection();
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
    // DHT11 sensor can only be read every 2 seconds.
    interruptibleDelay(2000);
}

void handleAutoFanCooling()
{
    if (temp < medWarm)
    {
        analogWrite(motorPin_1, 0);
        analogWrite(motorPin_2, 0); // stop motor: both inputs LOW
        Serial.println(F("Fan OFF"));
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

// --- Rain Response ---
void handleRainResponse()
{
    processFireDetection();
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
    interruptibleDelay(500);
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

// OLED Display
void handleDisplay()
{
    if (!oledReady)
    {
        return;
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    // Row 1
    display.setCursor(0, 0);
    if (fireDetected)
    {
        display.println(F("!! FIRE !!"));
        display.setCursor(0, 16);
        display.println(F("Fan OFF / Alarm"));
        display.display();
        return;
    }

    display.print(F("Temp: "));
    display.print(temp, 1);
    display.println(F(" C"));

    // Row 2
    display.setCursor(0, 16);
    display.print(F("Hum: "));
    display.print(humi, 1); // print temperature with no decimal places
    display.println(F("%"));

    display.display(); // send all text to OLED
}