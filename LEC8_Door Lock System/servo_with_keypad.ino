#include <Keypad.h> // use keypad library
#include <Servo.h>  // use Servo library
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
// create keypad object
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins,
                         colPins, rows, cols);
Servo myServo; // create servo object to control a servo
// setup passcode
String cor_Passcode = "123A"; // correct passcode
String ent_Passcode;          // entered passcode

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("Keypad is ready! Press any key...");
    myServo.attach(servoPin); // attaches servo to pin 13
}

void loop()
{
    // put your main code here, to run repeatedly:
    // read key from keyboard
    char key = myKeypad.getKey();

    // print the key just read
    if (key) {
        Serial.print("User pressed: ");
        Serial.println(key);
        if (key == '#')
        {
            // clear current input
            ent_Passcode = "";
            printCurInput();
        } else if (key == '*') {
            // submit passcode;
            submitAndCheck();
            // clear current input after submisssion
            ent_Passcode = "";
        } else {
            ent_Passcode += key;
            printCurInput();
        }
    }
}

void submitAndCheck() {
    if (ent_Passcode == cor_Passcode)
    {
        Serial.println("Correct passcode, please enter!");
        myServo.write(unlockDeg);
        delay(2000); // keep unlocked for user entering
        myServo.write(lockDeg);
    } else {
        Serial.println("Wrong passcode, please try again.");
    }
}

void printCurInput() {
    Serial.print("Current input: ");
    Serial.println(ent_Passcode);
}