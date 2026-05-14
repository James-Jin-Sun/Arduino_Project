int rainPin = A1;
int rainValue = 0;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    rainValue = analogRead(rainPin);

    Serial.print("Rain Value: ");
    Serial.println(rainValue);

    delay(500);
}