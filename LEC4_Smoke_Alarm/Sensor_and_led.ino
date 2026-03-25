int mq2Pin = A0;
int gasValue;
int gas_th = 350; // threhold of gas value
int ledPin = 2;

void setup()
{
    // put your setup code here, to run once:
    pinMode(mq2Pin, INPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600); // start serial comminication at 9600 baud
    pinMode(aBuzzer, OUTPUT);
}

void printValues()
{
    Serial.print("Value read from mq2Pin:");
    Serial.println(gasValue);
    // delay(1000);
}

void loop()
{
    // put your main code here, to run repeatedly:
    gasValue = analogRead(mq2Pin);
    printValues();
    if (gasValue >= gas_th)
    {
        digitalWrite(ledPin, HIGH);
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }
}
