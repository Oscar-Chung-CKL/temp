/* 

    I'm building on top of this code library to enable the index to correct against any vibrations to reduce overall errors as we're dead tracking.
    The goal of this set of code is first to return the position of the robot fish accurately. 
    Later, we would be able to specify it's position and write a position control loop, together with a speed loop for the robot fish. 
    First time doing controls! 

    For the differential turning, there isn't much, we simply do a bang-bang style of control. We have the paramter differential turn to simply set the speed differential. 
    I will keep building on it. 

    28/5/2022 - Timothy NG
 * 
 * 
 */

#include <Encoder.h>
#include <Servo.h>


#define ENCA 2
#define ENCB 10
#define ENCI  3
#define motorPin 9
#define leftFinPin  5
#define rightFinPin  6

#define debug_enc 0

//Communication Variables 
char inComingbyte[6] = {0};
int command_pitch = 0; 
int command_roll = 0; 
int command_yaw = 0; 
int command_speed = 0;
unsigned long int lastReceiveTime = 0;


// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder fish_Enc(2, 10);
Servo mainMotor;
Servo leftFin;
Servo rightFin;


bool flag = 0;
float turn_differential = 0.5;

const long gearRatio = 21;
const long cpt = 500*4;
const float count = cpt*gearRatio;

volatile long rotation_Index = 0;
long tick_Rev = 0;
long positionFin  = 0;
volatile long rotation_Count = 0;
volatile bool dir = 1;

//   avoid using pins with LEDs attached

void encoderInitialize(){
  //To distinguish between direction 
  int x = positionFin - fish_Enc.read();

  if(x < 0){
    dir = 1;
    rotation_Index++;
    fish_Enc.write(0);    
  }

  //for the clockwise case
  else if (x > 0){
    dir = 0;
    rotation_Index--;
    fish_Enc.write(0);
  } 
}

int yaw_turn(int, float, int); //receives direction input, and returns the altered PWM output for the motor. 
void encoder_home(); //sets the encoder home. 


void encoderLoop(){
  
  //To distinguish between direction 
  int x = positionFin - fish_Enc.read();
  
  //for the anticlockwise case
  if(rotation_Index == 0){
    if(x < 0){
      dir = 1;
      rotation_Index++;
      fish_Enc.write((rotation_Index-1)*cpt);
        if((rotation_Index-1) == gearRatio){
          rotation_Index = 1;
          rotation_Count++;
          fish_Enc.write(0);
        } 
    }
  
    //for the clockwise case
    else if (x > 0){
      dir = 0;
      fish_Enc.write((rotation_Index+1)*cpt); 
      if(rotation_Index+1 == -gearRatio){
          rotation_Index = -1;
          rotation_Count--;
          fish_Enc.write(0);
      } 
      rotation_Index--;
} 
  }
  else{
     if(x < 0){
      dir = 1;
      fish_Enc.write((rotation_Index)*cpt);
      
      if((rotation_Index) == gearRatio){
        rotation_Index = 1;
        rotation_Count++;
        fish_Enc.write(0);
      }
      rotation_Index++; 
    }
  
    //for the clockwise case
    else if (x > 0){
      dir = 0;
      rotation_Index--;
      fish_Enc.write((rotation_Index)*cpt); 
      if(rotation_Index == -gearRatio){
          rotation_Index = -1;
          rotation_Count--;
          fish_Enc.write(0);
      } 
    } 
  }

}

void setup() {
  Serial.begin(19200);
 
  //Serial.println("Robot Fish Encoder Test");
  tick_Rev = gearRatio*cpt;
  //Serial.print(tick_Rev);
  attachInterrupt(digitalPinToInterrupt(ENCI), encoderInitialize, RISING);
  
  //mainMotor.attach(motorPin);
  leftFin.attach(leftFinPin);
  rightFin.attach(rightFinPin);

  leftFin.write(90);
  rightFin.write(90);
 
  mainMotor.attach(motorPin);
  mainMotor.writeMicroseconds(1500);
  delay(100);

  
  //Serial.println("Please initialize the encoder by pushing it to the closest index");
  //align index with a zero to home the motor. 
  while(rotation_Index == 0){
    fish_Enc.write(0);
  }
  #if debug_enc
    Serial.println("The Encoder has been initialize! The current value of the encoder is: ");
    Serial.print(" Rotation = ");
    Serial.print(rotation_Count);
    Serial.print(" Index Count = ");
    Serial.print(rotation_Index);
    Serial.print(" Direction = ");
      if(dir){
        Serial.print("Anticlockwise");
      }
      else if(!dir){
        Serial.print("Clockwise");
      }
    Serial.println();
  #endif
  //Set home function, once the count and the index is aligned, then we will position the home function by calculating it's position relative to initial home. The count still refers 
  //to the first index. The home is simply an offset. 

  //upon initialization of the homing function, change the function to the loop function. 
  attachInterrupt(digitalPinToInterrupt(ENCI), encoderLoop, RISING);
}



void loop() {

  getData();

  
  //command speed is 0-9
  int pwm = map(command_speed, 0, 9, 0, 255);
  //Serial.print("speed is: ");
  //Serial.println(pwm);
  float cont_pwm = yaw_turn(pwm,turn_differential,command_yaw);
  cont_pwm = map(cont_pwm, 0, 255, 1500, 1800);
  mainMotor.writeMicroseconds(cont_pwm);
  doRollPitch(command_roll, command_pitch);

  

#if debug_enc
  long newFin;
  newFin = fish_Enc.read();
  if (newFin != positionFin) {
    Serial.print(" Rotation = ");
    Serial.print(rotation_Count);
    Serial.print(" Index Count = ");
    Serial.print(rotation_Index);
    Serial.print(" Fin Position = ");
    Serial.print(fish_Enc.read());
    positionFin = newFin;
  }
#endif



#if debug_enc
  Serial.print("Motor speed is : ");
  Serial.print(cont_pwm);
  Serial.println();
#endif

}

int pos_error = 0 ;

void goToPosition(int motorPosition, int motorSpeed){
  //receives the desired position to go to and executes the code to reach it. 
  int max_speed = map( motorSpeed, 0,10,1500,2000);
  
  //from an angle representation to a encoder index
  unsigned int target_pos = map(motorPosition, 0, 360, 0, count);
  if (dir){
   pos_error = (target_pos - fish_Enc.read());
  }
  else if(!dir) {
     pos_error =  target_pos + fish_Enc.read();
  }
  
  
  float x = 0.8*pos_error/count*300+1500;
  Serial.print(x);
  Serial.print("\t");
  Serial.print(" the target position is: ");
  Serial.print(target_pos);
  Serial.print("\t");
  
  if (x > max_speed)x = max_speed;
  if (x < 1500) x = 1500; // need to write code to reverse direction here. 
  if (x < 1200) x = 1200;
  if(!(abs(pos_error) < 0.1*count)) {
  mainMotor.writeMicroseconds(x);
  Serial.print("Position Error is ");
  Serial.println(pos_error);
  }
  else{
    mainMotor.writeMicroseconds(1000);
    delay(100);
    Serial.print("Reached Target");
  }
  //direct PWM test
  //x = map(x, 1200,1800, 0, 255);
  //analogWrite(motorPin,x);
}

int yaw_turn(int pwm, float diff, int turn){
  //Accepts a pwm signal and outputs a pwm signal from 0-255
  float enc_pos = abs(fish_Enc.read());
  float q1 = count*0.25;
  float q2 = count*0.4;
  float q3 = count*0.75;
  float q4 = count*0.9;
  if( (enc_pos > q1) && (enc_pos < q2)){
    float x = (1 + turn*diff)*pwm;
    //Serial.print(" turn differential signal in PWM terms is: ");
    //Serial.println(x);
    return x;
  }
  else if ( ( enc_pos > q3) && (enc_pos < q4)){
    float x = (1 - turn*diff)*pwm; 
    //Serial.print(" the other turn differential : ");
    //Serial.println(x);
    return x;

  }
  else {
    return pwm;
  }
  
}


char getData(){                  //data update from controller
//updates the speed, pitch, roll and yaw command 
//cmd signal would be : c speed(1) pitch(1) roll(1) yaw (1) e 
// the buffer would be of length 6.

    if(Serial.available()>=6){
      char x = Serial.read();
      if(x == 'c'){
        Serial.readBytesUntil('e',inComingbyte,5);
          //Cycles through the entire buffer and rocesses the information  
         command_speed    = inComingbyte[0] -'0';
         command_pitch    = inComingbyte[1] -'0';
         command_yaw      = inComingbyte[2] - '0';
         command_roll     = inComingbyte[3] -'0';
         //command_yaw      = inComingbyte[2] -'0'; 
         lastReceiveTime = millis();  
      }
 
    }

    if((millis() - lastReceiveTime) > 3000){
      command_speed = 0;  

      //Serial.println("killed");
      

    }
}

void doRollPitch(int roll, int pitch){
  //accepts the 0-9 directly
  float s1 = 0;
  float s2 = 0;
  float maxAngle = 45;


  // define roll signal to be a number from (-ve)1234 5 6789(+ve) 
  s1= ((4-roll)*maxAngle/8 +(4-pitch)*maxAngle/4)+ 90.0;
  s2= ((4-roll)*maxAngle/8 -(4-pitch)*maxAngle/4)+ 90.0;

  leftFin.write(s1);
  rightFin.write(s2);
 
}
