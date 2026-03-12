int ledPin = 2;
int pbPin = 7;
int buttonValue;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(pbPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonValue = digitalRead(pbPin);
  if(buttonValue == LOW){
  digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
}
