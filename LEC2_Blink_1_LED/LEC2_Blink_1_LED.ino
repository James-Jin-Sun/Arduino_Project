int ledPin = 2;
int ledPin_2 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin_2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin_2, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin_2, LOW);
  delay(1000);
}
