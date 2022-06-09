void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
}

bool ok(char cmd[]){
  int sum = 0;
  for (int i = 0; i < 6; i++){
    sum = sum + cmd[i];
  }
  return (sum >= 392 && sum <= 428);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (ok("cwwwwe") == true){
    Serial.println("no problem");
    Serial.flush();
  }
}
