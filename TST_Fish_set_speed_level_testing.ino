#include <Servo.h>

long int counter = 0;
const long int ticRatioMainMotor = 6000;
float rel_angle = 0;
volatile long int pos_Main=0;
#define ENCA 5 // YELLOW
#define ENCB 2 // WHITE
bool flag = true;
int idx = 0;
char cmd = '0';
int power = 0; //0-9
int turning = 0;//7-9
int throttle = 0;
Servo   pusherESC;  

#define THROTTLE_MIN        1500
#define THROTTLE_MAX        2000
#define THROTTLE_BRAKE       1000

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Attach the relative encoder to the ISR
  pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  attachInterrupt( digitalPinToInterrupt(ENCA), readEncoder_Main, RISING);
  pusherESC.attach(6);
  pusherESC.writeMicroseconds(THROTTLE_MIN);//calibration
  Serial.println("Arming........");   // just some display message 
  delay(2000);
   
}

void loop() {
  int j = 1;
  // put your main code here, to run repeatedly:
   //cmd = "00";
   int tem = pos_Main % 867 + 1;
   // mapping
   
   //Serial.println(pos_Main);
    if(Serial.available() > 1)
    {
      cmd = Serial.read();
      idx = cmd - '0';
      Serial.println(idx);
      Serial.readString(); // clear buffer
      throttle = map(idx,0,6,1500,2000);
      Serial.println(throttle);
    }
    
    if (Serial.available()>10){ // clear buffer
      while (Serial.available()>0){
        Serial.read();   
      }
    }

   pusherESC.writeMicroseconds(throttle);

 
}



void readEncoder_Main(){
 int b_A = digitalRead(ENCB);
  if(b_A > 0){
    pos_Main--;
  }
  else{
    pos_Main++;
    }
}
