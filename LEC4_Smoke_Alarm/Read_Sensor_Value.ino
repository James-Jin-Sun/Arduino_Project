int mq2Pin = A0;
int gasValue;

void setup()
{
    // put your setup code here, to run once:
    pinMode(mq2Pin, INPUT);
    Serial.begin(9600); // start serial comminication at 9600 baud
}

void loop()
{
    // put your main code here, to run repeatedly:
    gasValue = analogRead(mq2Pin);
    Serial.print("Value read from mq2Pin:");
    Serial.println(gasValue);
    delay(1000);
}
