/* Chem-E-Car Club Code
  Last Updated: Spring 2020
  Author: Nicholas Gildenhuys
*/

// no p_led, that is just hardwired as on
//#define P_LED_PIN  2 // defined as the LED for giving p_resistor steady signal
#define S_LED_PIN  13// using the built in LED for state
#define BUTTON_PIN  5// define as buttun pin
#define P_RESISTOR_PIN  A3//define as the photoresistor pin
#define MOS_PIN  2//defined as the pin outputing to the mosfet
#define TRANS 50//the transistion value to stop the solonoid at
// look at the iodine clock reaction graph for the curve 
// 50 was chosen from this graph

//int state   = 0; // not really used in final build
//int history = 0; // for later use if we need a better gauge of iodine cock value
int p_val;
/* void setup()

   Function:
      - Sets up the proper pins as inputs and outputs
      - begins serial communication with terminal for debugging
*/
void setup()
{
  Serial.begin(9600); // starts serial communication for debugging

  //pinMode(P_LED_PIN, OUTPUT); // sets the led pin as an output
  pinMode(S_LED_PIN, OUTPUT);
  pinMode(MOS_PIN, OUTPUT);
  pinMode(P_RESISTOR_PIN, INPUT); // sets the photo resistor pin to be an input
  pinMode(BUTTON_PIN, INPUT); // sets the button pin to be an input
  
  digitalWrite(S_LED_PIN, HIGH);
  //digitalWrite(BUTTON_PIN, HIGH);

}

/* void loop()

   Function: the main loop function, what is in here will loop over and over while the arduino is on.
      - Check if the button has been pressed to be start tracking photoresistor value
      - If pressed for a certain time, reset everything, if just momentary, pick up where ever it last left off
      - While tracking check for significant change (will require testing to figure out what that change will have to be
      - Once the proper change is seen by the resistor, send a HIGH to the MOSFET to turn ON/OFF (not sure what the prefered state is) the solonoid and signal a side LED that it's done
      - Once finished, exit and return to steady stat button input, and LED should show that it's in this state

*/
void loop()
{
  while(digitalRead(BUTTON_PIN)) delay(250); // wait to start the car

  // turn off status led pin
  digitalWrite(S_LED_PIN, LOW);
  // arm the solonoid
  digitalWrite(MOS_PIN, HIGH);
  delay(1000); // I know this is not the best way to do this
  do{
    p_val = analogRead(P_RESISTOR_PIN);
    Serial.println("Analog value: ");
    Serial.println(p_val);
    if(!digitalRead(BUTTON_PIN)) break;
    delay(100);
  }while(p_val > TRANS);
  digitalWrite(S_LED_PIN, HIGH);

  digitalWrite(MOS_PIN, LOW);
  delay(1000);// #badpractice 
}
