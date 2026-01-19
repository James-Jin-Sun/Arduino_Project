// C++ code
void setup()
{
  pinMode(2, OUTPUT);  // red
  pinMode(3, OUTPUT);  // blue
  pinMode(4, OUTPUT);  // yellow
  pinMode(5, OUTPUT);  // green
}
// 4 LED blink one by one 
void one_by_one(){
  digitalWrite(2, HIGH);
  delay(500);  // set to 500ms (0.5s) to make it faster
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(500);
}
// 4 LED blink in the same time
void in_the_same_time(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(300);  // set to 300ms (0.3s) to make it faster
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(300);  // add 1 more delay for the blinking to be visible
  
}
void loop()
{
  one_by_one();
  in_the_same_time();
  in_the_same_time();
  in_the_same_time();
}