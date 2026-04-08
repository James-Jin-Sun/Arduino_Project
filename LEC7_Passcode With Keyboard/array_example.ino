int numbers[5] = {10, 20, 30, 40, 50};
char letters[4] = {'A', 'B', 'C', 'D'};
int table[2][3] = {
    {1, 2, 3}, // Row 0
    {4, 5, 6}  // Row 1
};

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    Serial.println(letters[0]);  // A
    Serial.println(letters[3]);  // D
    Serial.println(numbers[1]);  // 20
    Serial.println(numbers[4]);  // 50
    Serial.println(table[0][0]); // 1
    Serial.println(table[1][2]); // 6
}