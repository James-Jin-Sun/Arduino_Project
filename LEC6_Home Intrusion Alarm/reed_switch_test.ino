int reedSwitch = 4;
bool reed_switch_value;

void setup(){
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(reedSwitch, INPUT);
}

void loop(){
    // put your main code here, to run repeatedly:
    reed_switch_value = digitalRead(reedSwitch);
    Serial.print("reedSwitch value: ");
    Serial.println(reed_switch_value);
}
