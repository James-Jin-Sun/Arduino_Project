int motorPin = 6;
int pbPin = 7;

bool cur_buttonValue;
bool pre_buttonValue = HIGH;

unsigned long startTime = 0;
unsigned long duration = 3000;

bool motorON = false;

void setup()
{
    pinMode(motorPin, OUTPUT);
    pinMode(pbPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    cur_buttonValue = digitalRead(pbPin);

    // TODO 1: detect button press (edge detection)
    if (cur_buttonValue == LOW && pre_buttonValue == HIGH)
    {
        // TODO 2: start motor + record time
        if (!motorON)
        {
            startTime = millis();
            analogWrite(motorPin, 255);
            motorON = true;
        }
    }
    // TODO 3: use millis() to stop motor after duration
    if (millis() - startTime >= duration && motorON)
    {
        analogWrite(motorPin, 0);
        motorON = false;
    }

    pre_buttonValue = cur_buttonValue;
}