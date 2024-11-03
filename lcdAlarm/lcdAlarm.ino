//arduino pojects for dummies alarm clock
//16x2 lcd display
//modified for i2c board(hw-113)
#include <Wire.h>  //i2c wire library for communication to the RTC(clock)
#include "RTClib.h"  //date and time functions for RTC
#include <LiquidCrystal.h> //display functions for LCD
#include <LiquidCrystal_I2C.h> //i2c library for i2c

RTC_DS3231 rtc;   //create real time clock
DateTime now;

boolean displayAlarmSet = false;  //show time mode or show alarm
boolean alarm = false;  //whether the alarm is happening
boolean armed = false; //alarm armed or not

int alarmHrs = 12;  //alarm time code
int alarmMins = 00;

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //create an LCD called lcd
LiquidCrystal_I2C lcd(0x27,16,2);

//user input to set alarm time
const int alarmSetPin=6; //used to change alarm set mode
const int incrementAlarmHrsPin = 7; //increment alarm hours in set mode
const int incrementAlarmMinsPin = 8;  //increment minutes in set mode
const int piezoPin = 9;   //buzzer pin
const int alarmArmedPin = 10;  //enable the alarm to go off

void updateDisplay(){
  if(displayAlarmSet){
    lcd.setCursor(0,0);
    lcd.print("Set alarm times: ");
    lcd.setCursor(4,1);
    lcd.print(" ");
    lcd.setCursor(5,1);
    if(alarmHrs<10){
      lcd.print(0);
    }
    lcd.print(alarmHrs);
    lcd.setCursor(7,1);
    lcd.print(":");
    lcd.setCursor(8,1);
    if(alarmMins<10){
      lcd.print(0);
    }
    lcd.print(alarmMins);
    lcd.setCursor(10,1);
    lcd.print("  ");
  }
  else{
    int h = now.hour(); //get the hors right now
    int m = now.minute();
    int s = now.second();

    lcd.setCursor(0,0); //set cursor to (0,0) position
    if(armed){
      lcd.print("* The time is: ");
    }
    else{
      lcd.print(" The time is: "); // .. with spaces to clear chars
    }
    lcd.setCursor(4,1); //move to 4 on the second row
    if(h<10){   //add a zero if necessary
      lcd.print(0);  
    }
    lcd.print(h); //display hour
    lcd.setCursor(6,1); //move to next column
    lcd.print(":"); //colon
    lcd.setCursor(7,1); //next column
    if(m<10){
      lcd.print(0); //add zero if necessary
    }
    lcd.print(m);   //display minute
    lcd.setCursor(9,1); //move cursor
    lcd.print(":"); //colon
    lcd.setCursor(10,1); //move cursor
    if(s<10){    //maybe zero
      lcd.print(0);
    }
  lcd.print(s);//display seconds
  }
}

void checkAlarm(){
  if(alarmHrs==now.hour() && alarmMins==now.minute() && now.second()==0){
    alarm=true; //set alarm if alarm time equals now time
  }
}

void setAlarm(){
  int hrs=digitalRead(incrementAlarmHrsPin);
  int mins=digitalRead(incrementAlarmMinsPin);

  if(hrs==HIGH){
    alarmHrs+=1;  //increment hours upward
    delay(200);  //wait between incrementing numbers)
    if(alarmHrs>23){
      alarmHrs=0;
    }
  }
  if(mins==HIGH){
    alarmMins+=1;
    delay(200);
    if(alarmMins>59){
      alarmMins=0;
    }
  }
}
void soundAlarm(){
  float alarmFrequency=1400;  //value for the tone
  float period=(1.0/alarmFrequency) *100000;
  long beepDuration=250000; //time in microseconds
  long elapsedTime = 0;

  while(elapsedTime<beepDuration){
    digitalWrite(piezoPin,HIGH);
    delayMicroseconds(period/2);
    digitalWrite(piezoPin,LOW);
    delayMicroseconds(period/2);
    elapsedTime += (period);
  }
  digitalWrite(piezoPin, LOW);
  delayMicroseconds(beepDuration);

  //listen for button press or alarm to turn off
  int hrs=digitalRead(incrementAlarmHrsPin);
  int mins=digitalRead(incrementAlarmMinsPin);

  if(hrs==HIGH || mins==HIGH){
    alarm=false;
  }
}
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
 
  
  Wire.begin();   //enables communications for the LCD
  rtc.begin();    //enables RTC
  //lcd.begin(16, 2); //enables lcd
  lcd.print(" It's Alive!");    //print message, centered to confirm functionality
  
  delay(5000);   //wait to read message
  lcd.clear();  //clear

  //set several pins for input and output
  pinMode(alarmSetPin, INPUT);
  pinMode(incrementAlarmHrsPin, INPUT);
  pinMode(incrementAlarmMinsPin, INPUT);
  pinMode(alarmArmedPin, INPUT);
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  now = rtc.now();    //get current time
  int alarmArmed=digitalRead(alarmArmedPin);

  if (alarmArmed == HIGH){
    armed=true;
  } else{
    armed=false;
  }

  //determin if sounding or not
  if(armed){        //if alarm is armed
    if(!alarm){     //and if we are not sounding
      checkAlarm(); //check to see if it is time to trigger
    }
    else{
      soundAlarm(); //otherwise, we should be sounding the alarm
    }
  }

  //check whether we are in alarm set mode
  int setMode = digitalRead(alarmSetPin); //read pin on jumper
  if(setMode==HIGH){    //if pin is high
    displayAlarmSet=true;   //set alarmset to true to display alarm set mmenu
    setAlarm();         //go read switches to set alarm
  } else{     //if not in set mode
    displayAlarmSet=false;  //we are not in set mode
  }
  //refresh
  updateDisplay();
}
