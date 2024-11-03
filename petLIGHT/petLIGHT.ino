//light pet from  arduino projects for dummies
//randomly selects and fades through colors

//set pins for colors
const int redLED = 11;
const int blueLED = 10;
const int greenLED = 9;

//assign variables
int redValue = 0; //current brightness
int newRedValue = 0; //new brightness

int blueValue = 0;
int newBlueValue = 0;

int greenValue = 0;
int newGreenValue = 0;

//assign "utility" variables for the random number and fade speed
int randomValue = 0;
int fadeSpeed = 50;
int sadSpeed = 100;
int happySpeed = 150;

// mood selection
int mood = 0;
const int moodTime = 10000;  //time to wait in milliseconds(10 seconds)
//setup the three pins as OUTPUT
void setup(){

  Serial.begin(9600);   //setup serial port for testing
  Serial.println("start");

  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}
void blendColors(){
  Serial.println("chillin");
  newRedValue = random(255); //pick random value for red

  if(redValue < newRedValue){
    for (int x=redValue; x<newRedValue; x++){
      analogWrite(redLED, x);
      delay(fadeSpeed);
    }
  }
  else {
    for(int x=redValue; x>newRedValue; x--){
      analogWrite(redLED, x);
      delay(fadeSpeed);
    }
  }
  redValue=newRedValue;
  //set the value for green LED
  newGreenValue=random(255);
  if(greenValue<newGreenValue){
    for(int x=greenValue; x<newGreenValue; x++){
      analogWrite(greenLED, x);
      delay(fadeSpeed);
    }
  }
  else{
    for(int x=greenValue; x>newGreenValue; x--){
      analogWrite(redLED, x);
      delay(fadeSpeed);
    }
  }
  greenValue=newGreenValue;
  //set blue
  newBlueValue=random(255);
  if(blueValue < newGreenValue){
    for(int x=blueValue; x <newBlueValue; x++){
      analogWrite(blueLED, x);
      delay(fadeSpeed);
    }
  }
  else{
    for( int x=blueValue; x >newBlueValue; x--){
      analogWrite(blueLED, x);
      delay(fadeSpeed);
    }
  }
  blueValue = newBlueValue;
}
void purr(){
  Serial.println("purr");
  for(int count=0; count<10; count++){
    for(int x=0; x<255; x++){
      analogWrite(redLED, x);
      analogWrite(greenLED, x);
      analogWrite(blueLED, x);
      delay(10);
    }
    for(int x=255; x>0;x--){
      analogWrite(redLED,x);
      analogWrite(greenLED, x);
      analogWrite(blueLED, x);
      delay(10);
    }
  }
}
void happy(){
  Serial.println("happy");
  for(int x=greenValue; x<255; x++){
    analogWrite(greenLED, x);
    delay(happySpeed);
  }
  for(int x=redValue; x>0; x--){
    analogWrite(redLED, x);
    delay(happySpeed);
  }
  for(int x=blueValue; x>0; x--){
    analogWrite(blueLED, x);
    delay(happySpeed);
  }
  delay(moodTime);    //sets how long the pet will wait in this mood

  for(int x=255; x>0; x--){   //fade to black
    analogWrite(greenLED, x);
    delay(happySpeed);
  }
}
void sad(){
  Serial.println("sad");
  for(int x=redValue; x<255; x++){
    analogWrite(redLED, x);
    delay(sadSpeed);
  }
  for(int x=blueValue; x>0; x--){
    analogWrite(blueLED, x);
    delay(sadSpeed);
  }
  for(int x=greenValue; x>0; x--){
    analogWrite(greenLED, x);
    delay(sadSpeed);
  }
  delay(moodTime);  //how long to be in mood state
  for(int x=255; x>0; x--){
    analogWrite(redLED, x);
    delay(sadSpeed);
  }
}

void loop(){
  mood = random(20);  //pick random number to set the mood 0-19 highest not included
  Serial.print("figuring:"); Serial.println(mood);
  if(mood == 0){ // purr
    purr();
    }
  if(mood == 1){
    happy();
  }
  if(mood == 2){
    sad();
  }
  if(mood > 2){       //if the number is higher than 2 run color blend
    blendColors();
  }
}