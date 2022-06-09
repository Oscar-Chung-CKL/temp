int FirstShotX , FirstShotY;
void setup()
{
for(int i=2; i<9; i++)
{
pinMode(i, INPUT);
digitalWrite(i, 1);
}
Serial.begin(9600);
FirstShotX = 0;
FirstShotY = 0;
}


void loop(){
    
    int i, someInt, flag = 0;
    for(i=2; i<9; i++)
    {
      someInt = digitalRead(i);
      if(someInt == 0)
      {
        flag =1;
        break;
      }
    }
    if(flag == 1)
    {
        switch(i)
        {
          case 2: Serial.println("--------> Button A"); break;
          case 3: Serial.println("--------> Button B"); break;
          case 4: Serial.println("--------> Button C"); break;
          case 5: Serial.println("--------> Button D"); break;
          case 6: Serial.println("--------> Button E"); break;
          case 7: Serial.println("--------> Button F"); break;
          case 8: Serial.println("--------> Button KEY"); break;
          default: break;
        }
        flag=0;
    }
    
    int sensorValue = analogRead(A0);
    
    if(FirstShotX == 0)
    {
        FirstShotX = sensorValue;
        Serial.print("FirstShotX = ");
        Serial.println(FirstShotX);
    }
    
    Serial.print("X = ");
    Serial.println(sensorValue - FirstShotX);
    sensorValue = analogRead(A1);
    
    if(FirstShotY == 0)
    {
      FirstShotY = sensorValue;
    }
}
