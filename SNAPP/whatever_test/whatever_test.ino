
enum buttons {
  LEFT, RIGHT, UP, DOWN
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(33, HIGH);
}

void loop() {
  long int x = 123456789;
  // put your main code here, to run repeatedly:
  //Serial.println( (String) LEFT + " " + RIGHT + " " + UP + " " + DOWN);
  Serial.println(x);
}
