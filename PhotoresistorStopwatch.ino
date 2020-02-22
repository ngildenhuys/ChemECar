/* StopWatch
 * Paul Badger 2008
 * Demonstrates using millis(), pullup resistors, 
 * making two things happen at once, printing fractions
 *
 * Physical setup: momentary switch connected to pin 4, other side connected to ground
 * LED with series resistor between pin 13 and ground
 */
 
/* Modified to change out the end function of the momentary switch.
   A photoresistor now serves to stop the clock at three separate trigger
   points such that multiple outputs can be read
   By: Dan Schillizzi
   For the use of Purdue ChemE car 2017
*/


#define ledPin 2                  // LED connected to digital pin 2
#define buttonPin 3               // button on pin 3
#define pause 5                  // debouncing pause value

const int triggerOne = 7;  //This is the upper trigger level, the lower the value, the darker the trigger
const int triggerTwo = 6;  //This is the middle trigger level, the lower the value, the darker the trigger
const int triggerThree = 5;  //This is the lower trigger level, the lower the value, the darker the trigger

int value = HIGH;                   // previous value of the LED
int buttonState;                    // variable to store button state
int resistorStateOne;               // variable to store first resistor state
int resistorStateTwo;               // variable to store second resistor state
int resistorStateThree;             // variable to store third resistor state
int doneOne = 0;                    // first check is done
int doneTwo = 0;                    // second check is done
int doneThree = 0;                  // third check is done
int lastButtonState;                // variable to store last button state
int blinking;                       // condition for blinking - timer is timing
long interval = 100;                // blink interval - change to suit
long previousMillis = 0;            // variable to store last time LED was updated
long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch
int fractional;                     // variable used to store fractional part of time
int pResistor = A4;
int pValue;



void setup()
{
   Serial.begin(9600);

   pinMode(ledPin, OUTPUT);         // sets the digital pin as output
   pinMode(pResistor, INPUT);       // Set pResistor - A4 pin as an input 
   pinMode(buttonPin, INPUT);       // not really necessary, pins default to INPUT anyway
   digitalWrite(buttonPin, HIGH);   // turn on pullup resistors. Wire button so that press shorts pin to ground.


}


   void loop()

{
   // check for photoresistor state change
   pValue = analogRead(pResistor);
   
   // state for trigger one, HIGH means triggered (value has gone below it)
   if (pValue > triggerOne){
     resistorStateOne = LOW;
   }
   else{
     resistorStateOne = HIGH;
   }   
   
   // state for trigger Two, HIGH means triggered (value has gone below it)
   if (pValue > triggerTwo){
     resistorStateTwo = LOW;
   }
   else{
     resistorStateTwo = HIGH;
   }  
   
   // state for trigger Three, HIGH means triggered (value has gone below it)
   if (pValue > triggerThree){
     resistorStateThree = LOW;
   }
   else{
     resistorStateThree = HIGH;
   }  

   // check for button press
   buttonState = digitalRead(buttonPin);                   // read the button state and store



   if (buttonState == LOW && lastButtonState == HIGH  &&  blinking == false){     // check for a high to low transition

      // if true then found a new button press while clock is not running - start the clock



      startTime = millis();                                   // store the start time

      blinking = true;                                     // turn on blinking while timing

      delay(pause);                                               // short delay to debounce switch

      lastButtonState = buttonState;                     // store buttonState in lastButtonState, to compare next time



   }



   else if (resistorStateOne == HIGH && resistorStateTwo == LOW && resistorStateThree == LOW && blinking == true && doneOne == 0){     // check for a high to low transition

        doneOne = 1;

      // if true then value has fallen below trigger point one - report to serial monitor

        elapsedTime =   millis() - startTime;              // store elapsed time
        
        delay(pause);                                          // short delay to debounce switch

        lastButtonState = buttonState;                     // store buttonState in lastButtonState, to compare next time



       // routine to report elapsed time 

        Serial.print( (int)(elapsedTime / 1000L));         // divide by 1000 to convert to seconds - then cast to an int to print

        Serial.print(".");                             // print decimal point
    
       // use modulo operator to get fractional part of time 

       fractional = (int)(elapsedTime % 1000L);

       // pad in leading zeros - wouldn't it be nice if 

       // Arduino language had a flag for this? :)

       if (fractional == 0)

          Serial.print("000");      // add three zero's

       else if (fractional < 10)    // if fractional < 10 the 0 is ignored giving a wrong time, so add the zeros

          Serial.print("00");       // add two zeros

       else if (fractional < 100)

          Serial.print("0");        // add one zero

       Serial.print(fractional);  // print fractional part of time 
       
       Serial.print(" seconds to trigger first point (value of ");
       
       Serial.print(triggerOne);
       
       Serial.println(" for first trigger point)");



   }


   else if (resistorStateOne == HIGH && resistorStateTwo == HIGH && resistorStateThree == LOW && blinking == true && doneTwo == 0){     // check for a high to low transition

        doneTwo = 1;

      // if true then value has fallen below trigger point Two - report to serial monitor

        elapsedTime =   millis() - startTime;              // store elapsed time

        delay(pause);                                          // short delay to debounce switch
        
        lastButtonState = buttonState;                     // store buttonState in lastButtonState, to compare next time



       // routine to report elapsed time 

        Serial.print( (int)(elapsedTime / 1000L));         // divide by 1000 to convert to seconds - then cast to an int to print

        Serial.print(".");                             // print decimal point
    
       // use modulo operator to get fractional part of time 

       fractional = (int)(elapsedTime % 1000L);

       // pad in leading zeros - wouldn't it be nice if 

       // Arduino language had a flag for this? :)

       if (fractional == 0)

          Serial.print("000");      // add three zero's

       else if (fractional < 10)    // if fractional < 10 the 0 is ignored giving a wrong time, so add the zeros

          Serial.print("00");       // add two zeros

       else if (fractional < 100)

          Serial.print("0");        // add one zero

       Serial.print(fractional);  // print fractional part of time 
       
       Serial.print(" seconds to trigger second point (value of ");
       
       Serial.print(triggerTwo);
       
       Serial.println(" for second trigger point)");


   }

   else if (resistorStateOne == HIGH && resistorStateTwo == HIGH && resistorStateThree == HIGH && blinking == true && doneThree == 0){     // check for a high to low transition

        doneThree = 1;

      // if true then value has fallen below trigger point three - report to serial monitor

        elapsedTime =   millis() - startTime;              // store elapsed time

        blinking = false;                                  // turn off blinking, all done timing

        delay(pause);                                          // short delay to debounce switch
        
        lastButtonState = buttonState;                     // store buttonState in lastButtonState, to compare next time



       // routine to report elapsed time 

        Serial.print( (int)(elapsedTime / 1000L));         // divide by 1000 to convert to seconds - then cast to an int to print

        Serial.print(".");                             // print decimal point
    
       // use modulo operator to get fractional part of time 

       fractional = (int)(elapsedTime % 1000L);

       // pad in leading zeros - wouldn't it be nice if 

       // Arduino language had a flag for this? :)

       if (fractional == 0)

          Serial.print("000");      // add three zero's

       else if (fractional < 10)    // if fractional < 10 the 0 is ignored giving a wrong time, so add the zeros

          Serial.print("00");       // add two zeros

       else if (fractional < 100)

          Serial.print("0");        // add one zero

       Serial.print(fractional);  // print fractional part of time 
       
       Serial.print(" seconds to trigger third point (value of ");
       
       Serial.print(triggerThree);
       
       Serial.println(" for third trigger point)\n");


   }

 

   else if (doneOne == 1 && doneTwo == 1 and doneThree == 1){
      
      doneOne = 0;
      doneTwo = 0;
      doneThree = 0;
      
      lastButtonState = buttonState;                         // store buttonState in lastButtonState, to compare next time

   }
   
   else{
      
      lastButtonState = buttonState;                         // store buttonState in lastButtonState, to compare next time

   }



   // blink routine - blink the LED while timing

   // check to see if it's time to blink the LED; that is, the difference

   // between the current time and last time we blinked the LED is larger than

   // the interval at which we want to blink the LED.



   if ( (millis() - previousMillis > interval) ) {



      if (blinking == true){

         previousMillis = millis();                         // remember the last time we blinked the LED



         // if the LED is off turn it on and vice-versa.

         if (value == LOW)

            value = HIGH;

         else

            value = LOW;

         digitalWrite(ledPin, value);

      }

      else{

         digitalWrite(ledPin, LOW);                         // turn off LED when not blinking

      }

   }



}
