//Headers
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
#include <Servo.h>
//pins intialisations
int pot_speed=A15;
int servoPin = 8; 
#define button      0    //BUTTONS
#define buttonleft  1
#define buttonright 2
#define trigPinleft 41    //Ultrasonic pins
#define echoPinleft 40
#define trigPinright 31
#define echoPinright 30
#define buz 14
#define CS 48
#define DC 50

// variable intialisations
int pot_value=0;
int pot_value_mapped=0;
int warning=0;
int buttonstate=0;
int buttonstateleft=0;
int buttonstateright=0;
int car_speed=0;
long duration1, distance1,duration2, distance2;
//function intialisation
void overspeed_checking();
void show_speed();
void leftlanechecking();
void rightlanechecking();
void dooropenchecking();

Servo Servo1;
TFT_ILI9163C tft = TFT_ILI9163C(CS, 8, DC);  

void setup()                                        // setup
{
  Serial.begin(9600);
  Servo1.attach(servoPin);
  tft.begin();
  tft.fillScreen();
  
  // setting up of pins
  pinMode(pot_speed,INPUT);
  pinMode(button, INPUT);
  pinMode(buttonleft, INPUT);
  pinMode(buttonright, INPUT);
  pinMode(trigPinleft, OUTPUT);
  pinMode(echoPinleft, INPUT);
  pinMode(trigPinright, OUTPUT);
  pinMode(echoPinright, INPUT);
  pinMode(7, OUTPUT);
  pinMode(buz,OUTPUT);


} // Bracket of setup



void loop()
{
  
  
  buttonstate = digitalRead(button);
  buttonstateleft = digitalRead(buttonleft);
  buttonstateright = digitalRead(buttonright);
  //pot connections
  pot_value=analogRead(pot_speed);
  car_speed=map(pot_value,0,1024,0,180); 
  delay(1);
  digitalWrite(buz,LOW);
if (buttonstate==1 && buttonstateleft==0 && buttonstateright==0)  // Vechile on condition
   {
     show_speed();
     overspeed_checking();
   }//button==1 && buttonleft==0 && buttonright==0


if (buttonstate==1 && buttonstateleft==1 && buttonstateright==0)  // vechine on and Left idnicator on condition
   {
     show_speed();
     overspeed_checking();
     leftlanechecking();
   }  


if (buttonstate==1 && buttonstateleft==0 && buttonstateright==1)  // vechine on and right idnicator on condition
   {
     show_speed();
     overspeed_checking();
     rightlanechecking();
   }  


if (buttonstate==0 && buttonstateleft==0 && buttonstateright==0)  // vechine OFF condition
   {
    dooropenchecking();
   }  
} // bracket of loop



//                     Functions   


void overspeed_checking()
{
  pot_value=analogRead(A0);
  car_speed=map(pot_value,0,1024,0,180);
  if (car_speed>100)
  {
  tft.setCursor(20,30);
  tft.setTextSize(1);
  tft.println("OVER SPEED!!");
  digitalWrite(buz,HIGH); 
  delay(1000);
  warning ++; 
  if (warning>10)
   {
    //GSM sending message
   }//warning>10
  }
}//overspeed_checking

void show_speed()
{
        pot_value=analogRead(A0);
        car_speed=map(pot_value,0,1024,0,180);
        tft.setCursor(30, 50);
        tft.setTextColor(WHITE);  
        tft.setTextSize(3);
        tft.fillScreen();
        tft.println(car_speed);
}//show_speed


void leftlanechecking()
{
 
      digitalWrite(trigPinleft, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPinleft, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPinleft, LOW);
      duration2 = pulseIn(echoPinleft, HIGH);
      distance2 = (duration2/2) / 29.1;
      delay(10);
      if (distance2>0 && distance2<10)
      {
        tft.setCursor(30, 50);
        tft.setTextColor(WHITE);  
        tft.setTextSize(1);
        tft.fillScreen();
        tft.println("Warning !!");
        digitalWrite(buz,HIGH);
        delay(1000);
      }
      
             
}


void rightlanechecking()
{
 
      digitalWrite(trigPinright, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPinright, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPinright, LOW);
      duration1 = pulseIn(echoPinright, HIGH);
      distance1 = (duration1/2) / 29.1;
      delay(10);
      if (distance1>0 && distance1<10)
      {
        tft.setCursor(30, 50);
        tft.setTextColor(WHITE);  
        tft.setTextSize(1);
        tft.fillScreen();
        tft.println("Warning !!");
        digitalWrite(buz,HIGH);
        delay(1000);
      }
      
             
}

void dooropenchecking()
{
      digitalWrite(trigPinleft, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPinleft, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPinleft, LOW);
      duration2 = pulseIn(echoPinleft, HIGH);
      distance2 = (duration2/2) / 29.1;
      delay(10);
      if (distance2>0 && distance2<10)
      {
        //servo motor movement
      }
      

      digitalWrite(trigPinright, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPinright, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPinright, LOW);
      duration1 = pulseIn(echoPinright, HIGH);
      distance1 = (duration1/2) / 29.1;
      delay(10);
      if (distance1>0 && distance1<10)
      {
        //servo motor movement
      }
        
}

