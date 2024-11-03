  /*blinking light
  let the games begin
  setup is for initialization since it only runs once at the start
  */
  
  //pin 13 internally connected to on board LED
int LED = 8;

void setup() {


  //initialize digital pin as an output instead of input
  pinMode(LED, OUTPUT);

}

void loop() {
  // main routine to flash the led( will run forever with power)
  digitalWrite(LED, HIGH);  //tuns LED on (HIGH is voltage level)
  delay(150);              //wait
  digitalWrite(LED, LOW);   //make it low
  delay(1300);              //wait again

}
