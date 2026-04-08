#include <Keypad.h> // use keypad library
// step 1: define keyboard pins
int row_1 = 11;
int row_2 = 10;
int row_3 = 9;
int row_4 = 8;
int col_1 = 7;
int col_2 = 6;
int col_3 = 5;
int col_4 = 4;

// step 2: define keyboard size
const int rows = 4;
const int cols = 4;

// step 3: define keypad layout
char keys[rows][cols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// step 4: connect keypad pins
byte rowPins[rows] = {row_1, row_2, row_3, row_4}; // connect to row 1 to 4
byte colPins[cols] = {col_1, col_2, col_3, col_4}; // connect to col 1 to 4

// step 5: create keypad object
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins,
                         colPins, rows, cols);

void setup()
{
    // put your setup code here, to run once
    Serial.begin(9600);
    Serial.println("Keypad is ready! Press any key...");
}

void loop()
{
    // put your main code here, to run repeatedly:
    // step 6: read key from keyboard
    char key = myKeypad.getKey();

    // step 7: print the key just read
    if (key)
    {
        Serial.print("User pressed: ");
        Serial.println(key);
    }
}