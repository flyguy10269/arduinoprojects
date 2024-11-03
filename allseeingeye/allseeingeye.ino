//arduino for dummies all seeing eye
//delay dimer between LEDs
volatile int delayTime = 60;

//variable for current LED
int currentLED = 4;

//variable for travel direction
int dir = 1;

//variable to store the last time something changed
long timeChanged = 0;

//array to hold the value of the LEDs
byte ledPin[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

void setup() {
  //set all pins as OUTPUT
  for (int i=0; i<10; i++){
    pinMode(ledPin[i], OUTPUT);
  }
  //record the time after setup
  timeChanged = millis();
}

void loop(){
  //check if it's been long enough
  if( (millis() - timeChanged) > delayTime){
    //turn off all LEDs
    for (int i=0; i<10; i++){
      digitalWrite(ledPin[i], LOW);
    }
    //current LED on
    digitalWrite(ledPin[currentLED], HIGH);
    // increase direction
    currentLED += dir;
    //if we are at the end of a row change direction
    if(currentLED == 9){
      dir = -1;
    }
    if(currentLED == 0){
      dir = 1;
    }
    //store current time as last changed time
    timeChanged = millis();
  }
  delayTime =  analogRead(0);
  delay(5);
}