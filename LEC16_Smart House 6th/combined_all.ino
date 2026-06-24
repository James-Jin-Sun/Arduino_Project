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
int buzeerPin = 7;
bool fireDetected = false;  // Flag to indicate if fire is detected
int countFire = 0;          // Counter for flame sensor readings
int countNoFire = 0;        // Counter for no fire readings
bool fireTriggered = false; // Flag to indicate if fire safety action has been triggered

// OLED display
int SCREEN_WIDTH = 128;
int SCREEN_HEIGHT = 64;
int OLED_ADDR = 0x3C; // I2C address for OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


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
    pinMode(buzeerPin, OUTPUT);
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
