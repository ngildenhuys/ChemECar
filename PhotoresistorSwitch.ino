/* Chem-E-Car Club Code
 * Last Updated: Spring 2020
 * Author: Nicholas Gildenhuys
 */


#define P_LED_PIN  // defined as the LED for giving p_resistor steady signal
#define S_LED_PIN  // defined as the signal led pin 
#define BUTTON_PIN  // define as buttun pin
#define P_RESISTOR_PIN  //define as the photoresistor pin
#define MOS_PIN  //defined as the pin outputing to the mosfet

/* void setup()
 * 
 * Function:
 *    - Sets up the proper pins as inputs and outputs
 *    - begins serial communication with terminal for debugging
 */
void setup()
{
   Serial.begin(9600); // starts serial communication for debugging

   pinMode(P_LED_PIN, OUTPUT); // sets teh led pin as an output
   pinMode(S_LED_PIN, OUTPUT);
   pinMode(MOS_PIN, OUTPUT);
   pinMode(P_RESISTOR_PIN, INPUT); // sets the photo resistor pin to be an input
   pinMode(BUTTON_PIN, INPUT); // sets the button pin to be an input

   digitalWrite(BUTTON_PIN, HIGH);
}


/* void loop()
 * 
 * Function: the main loop function, what is in here will loop over and over while the arduino is on.
 *    - Check if the button has been pressed to be start tracking photoresistor value
 *    - If pressed for a certain time, reset everything, if just momentary, pick up where ever it last left off
 *    - While tracking check for significant change (will require testing to figure out what that change will have to be 
 *    - Once the proper change is seen by the resistor, send a HIGH to the MOSFET to turn ON/OFF (not sure what the prefered state is) the solonoid and signal a side LED that it's done
 *    - Once finished, exit and return to steady stat button input, and LED should show that it's in this state
 *
 */

void loop()
{


}
