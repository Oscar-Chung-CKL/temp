/* 
 *  The controller code from May 31 2022
 *  Tim: idk how the previoud code works
 *  so we make a new one
 * 
 */

//For the screen setting
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Timers
long int timer1 = 0;       //store the time when transmiting
long int timer2 = 0;       //store the time when sending T signals
long int timer3 = 0;       //store the time when pressing left-right buttons
long int timer4 = 0;       //store the time when pressing up-down buttons
long int timer5 = 0;       //store the time when sending P signals
long int bounceDelay = 150;  // delay to avoid bounce on switch

//long int time_now;

//Variables for transmission
//signal1:R;     signal2:U;     signal3:T;      signal4:P
String sum_str;
char message[20];
int ascii_sum;     //checkSum value

//declare Funduino buttons
int leftbutton = 5;           
int rightbutton = 3;
int upbutton = 2;
int downbutton = 4;

//deBounce time of each button
long int leftDeBounce;
long int rightDeBounce;
long int upDeBounce;
long int downDebounce;

//buttons state
int leftState = HIGH;
int rightstate = HIGH;
int upState = HIGH;
int downState = HIGH;

int lastLeftState = LOW;
int lastRightState = LOW;
int lastUpState = LOW;
int lastDownState = LOW;

//Button default values
int xMap, yMap;
int tMap = 5;         //default value of turnVal
int pMap = 0;         //default value of power

//declare Funduino joystick
int sensorValueX = analogRead(A0);    
int sensorValueY = analogRead(A1);


void checkButton(int left, int right, int up, int down){

  if (left != lastLeftState){
    leftDeBounce = millis();
  }

  if (right  != lastRightState){
    rightDeBounce = millis();
  }

  if (up != lastUpState){
    upDeBounce = millis();
  }

  if (down != lastDownState){
    downDeBounce = millis();
  }
  
}

void setup() {
   // Setup Serial
  //Serial.begin(19200,SERIAL_8O1); // Hello, you might need to change it later
  Serial.begin(19200);




  // Setup Screen
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //Ive changed the address //already chill
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  //  display.display();
  //  delay(2000); // Pause for 2 seconds
  //  // Clear the buffer
  display.clearDisplay();

  // Draw BREED welcome message
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(SCREEN_WIDTH, 0);
  display.println("Welcome to");
  display.setTextSize(3); // Draw 2X-scale text
  display.println("BREED");
  display.display();

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(100);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...



  

  //Setup Funduino pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(leftbutton,INPUT_PULLUP);
  pinMode(rightbutton,INPUT_PULLUP);
  pinMode(upbutton,INPUT_PULLUP);
  pinMode(downbutton,INPUT_PULLUP);

}

void loop() {
  
//  time_now = millis();

  //Update control variables from buttons
  //Reading Joystick Value
  sensorValueX = analogRead(A0);
  sensorValueY = analogRead(A1);
  xMap = map(sensorValueX, 30, 1000 , 0, 9);
  yMap = map(sensorValueY, 30, 1000, 0, 9);

  // reading the state of each button
  int currentLeft = digitalRead(leftbutton);
  int currentRight = digitalRead(rightbutton);
  int currentUp = digitalRead(upbutton);
  int currentDown = digitalRead(downbutton);
  
  checkButton(currentLeft, currentRight, currentUp, currentDown);

  //Reading the left, right, up and down buttons
  if((digitalRead(leftbutton) == LOW) && tMap > 1) {
    
    if ( millis() -  timer3 > bounceDelay){
      tMap++;
        //Serial.println("button down");
        //delay(20);
        timer3 = millis();
    }
    
    
    tMap--;
        //Serial.println("button down");
        //delay(20);
        timer3 = millis();
        
  }
  else if ((digitalRead(rightbutton)== LOW) && tMap < 9) {

    /*
    if (millis() - timer3 > bounceDelay){

        tMap--;
        //Serial.println("button down");
        //delay(20);
        timer3 = millis();
      
      
    }
    */

    tMap++;
        //Serial.println("button down");
        //delay(20);
        timer3 = millis();
  }
  else if((digitalRead(downbutton) == LOW) && pMap > 0) {
    
    /*
     * if (millis() - timer4 > bounceDelay){
      pMap--;
        //Serial.println("button down");
        //delay(20);
        timer4 = millis();

    }
    */

    pMap--;
        //Serial.println("button down");
        //delay(20);
        timer4 = millis();
  }
  else if ((digitalRead(upbutton)== LOW) && pMap < 9) {
    /*
    if (millis() - timer4 > bounceDelay){
      pMap++;
        //Serial.println("button down");
        //delay(20);
        timer4 = millis();
    

    }
    */

    pMap++;
        //Serial.println("button down");
        //delay(20);
        timer4 = millis();
  }


  //Update Screen
  
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("PWM: ");
  display.println(pMap);
  // Turning control Left
  display.print("Turning:");
  int turnVal=tMap;
  if ((turnVal>=1) and (turnVal<=3)){
    display.print("LEFT => ");
    }
    // Going Straight
    else if ((turnVal>=4) and (turnVal<=6)){
      display.print("STRAIGHT => ");
    }
    // Turning control Right
    else if ((turnVal>=7) and (turnVal<=9)){
      display.print("RIGHT => ");
    }
  display.println(tMap);
  display.println("Servo:  ");
  display.print("X= ");
  display.print(xMap);
  display.print(", Y= ");
  display.print(yMap);
  display.println();
  display.display();
  
  
  // Send signal after every 100 ms
  if (millis() - timer1 > 100) {
    timer1=millis(); //update timer1

    // Prepare string and send to receiver

    //speed, pitch, roll, yaw, in that order
    sum_str = "c" + String(pMap) + String(yMap) + String(tMap) + String(xMap) + "e"; //payload + checksum
    strcpy(message,sum_str.c_str());
    Serial.print(message);

  }

}
