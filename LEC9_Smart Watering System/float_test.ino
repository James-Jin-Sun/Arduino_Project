void setup()
{
    Serial.begin(9600);

    int a = 5;
    int b = 2;

    float x = 5;
    float y = 2;

    Serial.println("=== INT vs FLOAT Demo ===");

    // Integer division
    int intResult = a / b;
    Serial.print("int result (5 / 2) = ");
    Serial.println(intResult);

    // Float division
    float floatResult = x / y;
    Serial.print("float result (5 / 2) = ");
    Serial.println(floatResult);

    // Mixed case
    float mixedResult = a / (float)b;
    Serial.print("mixed result (5 / 2) = ");
    Serial.println(mixedResult);
}

void loop()
{
    // nothing here
}