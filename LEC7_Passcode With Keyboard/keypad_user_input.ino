#include <Keypad.h> // use keypad library
// step 1: define keyboard size
const int rows = 4;
const int cols = 4;

// step 2: define keypad layout
char keys[rows][cols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
// step 3: connect keypad pins
byte rowPins[rows] = {11, 10, 9, 8};
byte colPins[cols] = {7, 6, 5, 4};

// step 4: create keypad object
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins,
                         colPins, rows, cols);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("Keypad is ready! Press any key...");
}

void loop()
{
    // put your main code here, to run repeatedly:
    // step 5: read key from keyboard
    char key = myKeypad.getKey();

    // step 6: print the key just read
    if (key)
    {
        Serial.print("User pressed: ");
        Serial.println(key);
    }
}