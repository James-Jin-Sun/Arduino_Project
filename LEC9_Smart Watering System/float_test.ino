void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    int a = 5;
    int b = 2;
    float x = 5;
    float y = 2;

    // Integer division
    int intResult = a / b;
    Serial.print("int result (5 / 2) = ");
    Serial.println(intResult);

    // Float division
    float floatResult = x / y;
    Serial.print("float result (5 / 2) = ");
    Serial.println(floatResult);

    // Mixed case 1
    float mixedResult = a / (float)b;
    Serial.print("mixed result_1 (5 / 2) = ");
    Serial.println(mixedResult);

    // Mixed case 2
    float mixedResult = (float)a / b;
    Serial.print("mixed result_2 (5 / 2) = ");
    Serial.println(mixedResult);
}

void loop()
{
    // put your main code here, to run repeatedly:
}