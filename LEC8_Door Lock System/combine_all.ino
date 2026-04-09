#include <Wire.h>              // use Wire library
#include <LiquidCrystal_I2C.h> // use LiquidCrystal(LCD) with I2C library

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup()
{
    // put your setup code here, to run once:
    lcd.init();      // initialize the lcd
    lcd.backlight(); // turn on backlight

    lcd.setCursor(0, 0); // move cursor to (0, 0)
    lcd.print("Keypad is ready! Press any key...");
    lcd.setCursor(0, 1); // move cursor to   (0, 1)
    lcd.print("User pressed: ");
}

void loop()
{
    // put your main code here, to run repeatedly:
}