int trigPin = ______; // TODO: set Trig pin number
int echoPin = ______; // TODO: set Echo pin number
unsigned long duration;
int distance;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(trigPin, ______); // TODO: OUTPUT or INPUT?
    pinMode(echoPin, ______); // TODO: OUTPUT or INPUT?
}

void loop()
{
    // put your main code here, to run repeatedly:
    digitalWrite(trigPin, LOW); // make sure trigger pin starts LOW
    delayMicroseconds(2);       // ensures a clean LOW

    // step 1:send a 10ms trigger pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // step 2: measure how long Echo pin stays HIGH
    duration = pulseIn(echoPin, HIGH);
    // step 3: convert time to distance
    distance = __________________________; // TODO: complete formula

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(300);
}