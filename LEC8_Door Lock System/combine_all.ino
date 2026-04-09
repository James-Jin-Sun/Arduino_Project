#include <Keypad.h>            // use keypad library
#include <Servo.h>             // use Servo library
#include <Wire.h>              // use Wire library
#include <LiquidCrystal_I2C.h> // use LiquidCrystal(LCD) with I2C library

const int rows = 4;
const int cols = 4;
int servoPin = 13;
int lockDeg = 90;  // 0 deg=lock
int unlockDeg = 0; // 90 deg=unlock
char keys[rows][cols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[rows] = {11, 10, 9, 8};
byte colPins[cols] = {7, 6, 5, 4};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins,
                         colPins, rows, cols); // create keypad object
Servo myServo;                                 // create servo object to control a servo
LiquidCrystal_I2C lcd(0x27, 16, 2);            // I2C address 0x27, 16 column and 2 rows

// setup passcode
String cor_Passcode = "123A"; // correct passcode
String ent_Passcode;          // entered passcode

void setup()
{
    // put your setup code here, to run once:
    lcd.init(); // initialize the lcd
    printInitMessage();
    myServo.attach(servoPin); // attaches servo to pin 13
}

void loop()
{
    // put your main code here, to run repeatedly:
    // read key from keyboard
    char key = myKeypad.getKey();

    // print the key just read
    if (key)
    {
        if (key == '#')
        {
            // clear current input
            ent_Passcode = "";
            printCurInput();
        }
        else if (key == '*')
        {
            // submit passcode;
            submitAndCheck();
            // back to initial screen

            // clear current input after submisssion
            ent_Passcode = "";
        }
        else
        {
            ent_Passcode += key;
            printCurInput();
        }
    }
}

void submitAndCheck()
{
    if (ent_Passcode == cor_Passcode)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Passcode OK");
        lcd.setCursor(0, 1);
        lcd.print("Door Opened");
        myServo.write(unlockDeg);
        delay(2000); // keep unlocked for user entering
        myServo.write(lockDeg);
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong Passcode");
        lcd.setCursor(0, 1);
        lcd.print("Pls Try Again");
    }
    delay(3000);        // give user enough time to read
    printInitMessage(); // go back to initial screen
}

void printCurInput()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Current input:");
    lcd.setCursor(0, 1);
    lcd.print(ent_Passcode);
}

void printInitMessage()
{
    lcd.clear();
    lcd.backlight();     // turn on backlight
    lcd.setCursor(0, 0); // move cursor to (0, 0)
    lcd.print("Enter passcode");
    lcd.setCursor(0, 1); // move cursor to   (0, 1)
    lcd.print("*=confirm #=clr");
}