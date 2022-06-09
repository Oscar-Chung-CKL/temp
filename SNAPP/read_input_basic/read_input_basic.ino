void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  // Serial1.begin(19200);
  // Serial2.begin(19200);
  // Serial3.begin(19200);
}

char c ;
int count = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    c = Serial.read();
    Serial.print(c);
    count ++;
  } 
}
