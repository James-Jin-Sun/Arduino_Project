#include <Adafruit_NeoPixel.h>

int LED_PIN = 6;    // Connect to D (DIN)
int LED_COUNT = 12; // 12 LEDs on ring

// NEO_GRB   → color order used by WS2812 LEDs (Green, Red, Blue)
// NEO_KHZ800 → communication speed (800 kHz signal required by WS2812)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Create a NeoPixel LED strip object

int flamePin = 3;
bool flameValue;
int buzeerPin = 7;

int motorPin_1 = 5; // DRV8833 IN1
int motorPin_2 = 9; // DRV8833 IN2

bool fireDetected = false; // Flag to indicate if fire is detected
int countFire = 0;     // Counter for flame sensor readings
int countNoFire = 0;   // Counter for no fire readings
bool fireTriggered = false; // Flag to indicate if fire safety action has been triggered

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(flamePin, INPUT);
    pinMode(buzeerPin, OUTPUT);
    strip.begin();
    strip.setBrightness(50); // Low brightness
    strip.show();            // send data to LED ring
    pinMode(motorPin_1, OUTPUT);
    pinMode(motorPin_2, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(flamePin), fireSafety, FALLING);
}

void loop()
{
    // put your main code here, to run repeatedly:
    checkFire();
    if (fireDetected)
    {
        Serial.println("Fire detected!");
        digitalWrite(buzeerPin, HIGH);
        setColor(255, 0, 0); // Red color for fire

        analogWrite(motorPin_1, 0);
        analogWrite(motorPin_2, 0); // Turn off the fan
    }
    else
    {
        Serial.println("No fire.");
        digitalWrite(buzeerPin, LOW);
        setColor(0, 0, 0); // Turn off LEDs

        // analogWrite(motorPin_1, 255);
        // analogWrite(motorPin_2, 0); // Turn on the fan at full speed
    }

     delay(1000);
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

void setColor(int r, int g, int b){
    for (int i = 0; i < LED_COUNT; i++)
    {
        strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
}