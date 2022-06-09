//Libraries
#include <Servo.h>

/*
 * Fixing up Saad's code. There are many things I would like to change, as I like my previous code more, but that will just be a lot of work. I need it to get it functional. 
 * will figure out how to make it tidy by using my own header files and function. 
 * 
 * Core things to have is a reliable communication system, will need to remove all the redundant signals. 
 * 
 * Just finished writing the encoder code that would allow us to measure position and speed. (relative to the starting position of course) 
 * We need to mechanically home it before starting. Add that at setup. 
 * 
 * Also change the comm signals by adding a 20 character requirement for the buffer before reading it. Removed the flush. 
 * Remember to add timer to the controller side. lets have it send signals every 50ms. 
 * 
 * 
 */

#define debug 0
//Servo
Servo servo1;
Servo servo2;
int servoPin1 = 11;
int servoPin2 = 9;
int initial1 = 90;
int initial2 = 90;
int min_angle = 0;
int max_angle = 180;
int mid_angle = 90;
int min_range = 0;
int max_range = 9;
int mid_range = 4;
float maxAttacAngle=40;

//Communication

float s1, s2;
bool check;
char incomingByte ='0';
String w;
String char1, char2, char3, char4;
int val1 = 0, val2 = 0, val3 = 0, val4 = 0;
float power = 0;          //Stores power value from controller

//Motor
unsigned int pwm_Pin1 = 8;
unsigned int pwm_Pin2 = 12;
float motor_Pwm = 0;
bool red_Flag = LOW;
bool on = LOW;

//encoder
unsigned long int timer1 = 0;
unsigned long int timer2 = 0;
long int counter = 0;
long int runtime = 0;
long int timer = 0;
float timeStep = 0;
long int encoderCounter = 0;
long int encoderRawVal = 0; //Global Variable for encoder absolute value
double angularVelocity[3] = {0, 0, 0};
long int counter2 = 0;
volatile long unsigned int speed_Counter = 0;
bool flag_Motion = false; // this flag checks if the motor is in motion, returns false if it is stalled. 


float frequency = 0;
long int t_initial = 0;

//Turn Differential
int turnVal = 5;        //Stores commmand value for control left and right. values 1-4 are left, 5 is straight, 6-9 are right
int oldTurnVal = 5;
int encoderVal = 0;         //stores value of encoder at any given time. Updates from interrupt.
float turn_Pwm = 0;         // Pwm value with differential applied
int oldPower = 5;
long int tailDelay1 = 2000;
int encoderPin0   =  29;
double diff = 0.5;              //to store the differential value corresponding to the signal
double stepDiff = 0.1;          //sets the differential value
int highcutoff, lowcutoff, offset;

//Kill Switch
long int killTimer; //timer for kill switch

//Motor control through ESC Driver
#define PIN_PUSHERESC       5     // PIN to control ESC, normally the white wire from ESC 
Servo   pusherESC; 
/*///////////////////////////////////////////////////////////////////////////////////////////////////////
 * The following are the setting for the ESC used, for other ESC, just chnage setting according to
 * ESC Spec
 *///////////////////////////////////////////////////////////////////////////////////////////////////////
#define THROTTLE_MIN        1500
#define THROTTLE_MAX        2000
#define THROTTLE_BAKE       1000
// End of ESC setting ///////////////////////////////////////////////////////////////////////////////////


//Relative Encoder Main Motor

#define ENCA 3 // YELLOW
#define ENCB 2 // WHITE
volatile long int pos_Main = 0;
const long int ticRatioMainMotor=6255; // Number of tic per revolution of the main motor. Implemnted to use the relative encoder as an absolute encoder temporarily. 
long int rotationCounter = 0;
long int prev_Ticks = 0;
long int delta_t = 0;



float rel_angle = 0;


void setup() {
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW); // Off to indicate still in setup
  
//Interrupt pin pullup relative encoder
  pinMode(ENCA,INPUT_PULLUP);
//  pinMode(ENCB,INPUT_PULLUP);
  
  //Initialize //Serial
 // Serial.begin(115200);
  Serial.begin(19200);
  while (!(Serial.available() || Serial.available()));     //Ensure fish does not start until there is a signal from comp or controller
  


  //Initialize Servo
  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  servo1.attach(servoPin1); // Attach servo pins
  servo2.attach(servoPin2);
  servo1.write(initial1); // Set Servo to defaults
  servo2.write(initial2);

  //Initialize PWM_pin for motor control 
  pinMode(pwm_Pin1, OUTPUT); // Set pwm pin
  pinMode(pwm_Pin2, OUTPUT); // Set pwm pin
  
  //Initialize timer
  killTimer = millis();

  attachInterrupt( digitalPinToInterrupt(ENCA), readEncoder_Main, RISING);
  
  Serial.println("Encoder Pins Initialized!");
  Serial.println("Setup is complete! Click to begin the program....");
  


  Serial.println("Arming........");   // just some display message 
    pusherESC.attach(PIN_PUSHERESC);
    pusherESC.writeMicroseconds(THROTTLE_MIN);

    t_initial = 0; //initiallize speed encoder;

  Serial.println("Arming........After delay");  
  
  //Setup complete prompt
  digitalWrite(11, HIGH); //To Check if setup complete
  Serial.println("Setup is complete!");

}

char cmd[12];    //to store the signal from transmitter

void loop() {
  
  
  if (Serial.available() > 20) {  //if bytes available to read in the buffer
    //Serial.println("I'm receiving: ");
    
    // clear out garbage until the start bit
    while (incomingByte != 'R'){
      incomingByte = Serial.read();
    }

    //Serial.readBytesUntil('?',cmd,11); 
        char cmd[12];    //to store the signal from transmitter

        int siglen = 0;  //to store the length of the incoming signal
     while (incomingByte != '?' and siglen<11) {  //read char by char until we know the end of signal is reached indicated by the identifier '?'
        cmd[siglen] = incomingByte;
        siglen++;
        incomingByte = Serial.read();    
    }

    //As we convert char array to string last element should exist and ideally must be the limiting character
    cmd[11]='\0';
    // TODO : print out cmd to check
    //Serial.println(cmd);
    //--------------------------------
    check = checkSum(incomingByte, siglen, cmd);
  
    if (check == true) {
      //Timer for kill switch. Note: Keep it in checksum condition as we want it to resume operation once proper signals are received and not due to interfering signals.
      killTimer = millis();

      //In incoming communication message: array[0] is 'R' or 'U' or 'T' or 'P' - convert to string, array[1:] are the numbers - convert to integer
      w = String(cmd);
      char1 = String(w[0]);
      val1 = String(w.substring(1, 2)).toInt();
      char2 = String(w[2]);
      val2 = String(w.substring(3, 4)).toInt();
      char3 = String(w[4]);
      val3 = String(w.substring(5, 6)).toInt();
      char4 = String(w[6]);
      val4 = String(w.substring(7, 8)).toInt();

      
      //Servo control expression. Linear combination of X and Y component of JoyStick
      s1= ((4-val1)*maxAttacAngle/5 +(4-val2)*maxAttacAngle/5)+ 90.0;
      s2= ((4-val1)*maxAttacAngle/5 -(4-val2)*maxAttacAngle/5)+ 90.0;
      
      if (char3 == "T") {
        turnVal = val3; // tail turning signal
      }
      if (char4 == "P") {
        power = val4 ; // power signal
      }

      //Send PWM signal to motor
      motor_Pwm = (power*255)/9.0;
      turn_Pwm = ((power*255)/9.0)*diff;
     
      //Servo motor angle is set
      servo1.write(s1);
      servo2.write(s2);

      
    }
    
    else {
      //Signal received but checksum not passed -> probably got interfered
      //Serial.print("Rejected! ----------------------------------------------------------------------------------------------");
    }
  }

      
    // CAUTION: Fish will turn on after kill switch activated once if signal is restored and checksum is passed
    killswitch();
    rel_Encoder();
     
    // Turning control Left
    if ((turnVal>=1) and (turnVal<=3)){
      //Serial.println("Turning Left");
       if (rel_angle< 180){
            motor_Pwm = ((power*255)/9.0)*diff;
      }
      else{
        motor_Pwm = (power*255)/9.0;
      } 
    }

    else if ((turnVal>=4) and (turnVal<=6)){
      //Serial.println("Going straight");
      motor_Pwm = (power*255)/9.0; //maps the value received (0-9) to (0-255)
    }

    // Turning control Right
    else if ((turnVal>=7) and (turnVal<=9)){
      //Serial.println("Turning Right");
      if (rel_angle > 180){
        motor_Pwm = (power*255)/9.0*diff;
      }
      else{
        motor_Pwm = ((power*255)/9.0);
      }
    }
  
   
  int throttle=map(motor_Pwm, 0, 255, THROTTLE_MIN, THROTTLE_MAX);
  pusherESC.writeMicroseconds(throttle);

      if (power==0){
        digitalWrite(13, LOW);
      }
      else{
        digitalWrite(13, HIGH);
      }


  #if debug
  //For debugging purposes, we can print everything on the Serial to test, just change debug to 1. 

    Serial.print("Encoder Items: ");
    Serial.print("\t");
    Serial.print(rotationCounter);
    Serial.print("\t");
    Serial.print(frequency); 
    Serial.print("\t");
    Serial.print(rel_angle);
    Serial.println();

    // Communication Items

    // Actuation Signals 
  #endif
}

void rel_Encoder(){

  long int x = pos_Main; //variable for current ticks
  if(prev_Ticks <= x );
  
  else{
    
    if(x < ticRatioMainMotor){
      rel_angle = (x/(ticRatioMainMotor*1.0))*360; //this is angle in degrees
    }
    else if ( x >= ticRatioMainMotor){
      // this command happense whenever we pass a turn
      
      pos_Main = x - ticRatioMainMotor; //reset the number of ticks
      prev_Ticks = x - ticRatioMainMotor; // the comparison for motion depends on the tick counter, which we reset after a full loop. Otherwise we can have tick count as two parts, like hour and minutes thing. 
      rotationCounter++; //keep track of the number of rotation
    }
    
    // Speed determination 
    if(speed_Counter > 10){
      int temp = millis(); //placeholder for the current time, so that all calculations reference this time
      delta_t = temp - t_initial;
    if (delta_t > 0) frequency = speed_Counter/(delta_t);
    t_initial = temp;
    prev_Ticks = x;
    speed_Counter = 0; 
    }   
  }
}


void killswitch(){
   if (millis() - killTimer > 3000) {
    power=0;
    motor_Pwm = 0;
    analogWrite(pwm_Pin1, 0);
    pos_Main = 0;
  }
}

//function for check sum
bool checkSum(char incomingByte, int siglen, char cmd[]) {
  check = false;
  int cSum=0;
  for (int c=0; c<8; c++){
    cSum+=cmd[c];
  }
  String numcheck = String(cmd[8]) + String(cmd[9]) + String(cmd[10]);
  int number = numcheck.toInt();
  if (cSum == number) {
    check = true;
  }
  return check;
}


void readEncoder_Main(){
  
    pos_Main++;
    speed_Counter++;

}
