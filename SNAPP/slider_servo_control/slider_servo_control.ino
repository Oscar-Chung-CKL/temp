
#include <Servo.h>

Servo arm;

int pin = 8;

bool ngt = false;

int btn = 7;

int VRx = A0;
int VRy = A1;

int x = -1;
int y = -1;

long int count = 0;
int val = -1;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pin, OUTPUT);
  pinMode(btn,INPUT);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);

  

  arm.attach(pin);

  arm.write(180);

}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(btn);

  if (val == LOW){
    arm.write(180);
    //Serial.println("low");
  }

  if (val == HIGH){
    arm.write(180);
    //Serial.println("high");
  }

  //delay(100);


}
