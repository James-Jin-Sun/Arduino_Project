int motorPin = 6;
int pbPin = 7;
bool cur_buttonValue;
bool pre_buttonValue = HIGH;
int state = 0;

void setup()
{
    pinMode(motorPin, OUTPUT);
    pinMode(pbPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    cur_buttonValue = digitalRead(pbPin);
    if (cur_buttonValue == LOW && pre_buttonValue == HIGH)
    {
        state = state + 1;
        if (state > 3)
        {
            state = 0;
        }
    }
    pre_buttonValue = cur_buttonValue;
    if (state == 0)
    {
        analogWrite(motorPin, 0);
        Serial.println(state);
    }
    else if (state == 1)
    {
        analogWrite(motorPin, 51);
        Serial.println(state);
    }
    else if (state == 2)
    {
        analogWrite(motorPin, 153);
        Serial.println(state);
    } // (state == 3)
    else
    {
        analogWrite(motorPin, 200);
        Serial.println(state);
    }
}