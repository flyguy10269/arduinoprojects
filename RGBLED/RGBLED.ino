//common cathode rgb led testing and messing around
const int redLED = 11;
const int blueLED = 9;
const int greenLED = 10;
volatile int pinToBlink;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

}

void myBlink(int pinToBlink){
  int pin = pinToBlink;
  digitalWrite(pin, HIGH);
  delay(1);
  digitalWrite(pin, LOW);
  delay(1);
}

void loop() {
  //myBlink(blueLED);
//  digitalWrite(redLED, HIGH);
//  digitalWrite(greenLED, HIGH);
//  digitalWrite(blueLED, HIGH);
//  myBlink(redLED);
//  myBlink(blueLED);
 // myBlink(greenLED);

}