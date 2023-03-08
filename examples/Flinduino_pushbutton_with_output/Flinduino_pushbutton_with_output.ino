#include <Pushbutton.h>             // this is the Pushbutton library from Pololu   -        see https://github.com/pololu/pushbutton-arduino


//pin definitions
const int MICROSWITCH = A4;        // input microswitch pin 
const int PUSHBUTTON = A5;          // input pushbutton pin
const int PROXSWITCH = 13;          // input for IR Proximitity sensor (digital)
const int RELAY = 12;                        // relay output



Pushbutton button(MICROSWITCH);              // creates a default  Pushbutton object on the MICROSWITCH pin (input, pullup,)

void setup()
{
  // start the serial port (USB) to provide information about what is happening
  Serial.begin(115200);
  delay(3000);  

  //configure relay as an output
  pinMode(RELAY, OUTPUT);

  
  // write locic low (0v) to the relay to ensure that it is stoped
  digitalWrite(RELAY, LOW);    

  Serial.println("setup complete, starting main loop");
}


void loop()
{
    Serial.println("Waiting for button press to start");
    button.waitForButton();      // blocking call - wiil wait here until the button is pushed and released (debounced)
    Serial.println("loop started...");
    Serial.println("relay will switch on when the button is pressed, and switch off when released.");

    while(1)        // always stay in this loop (1 is always true)
    {
        
         if (button.getSingleDebouncedPress())      // check for debounced button press (not - blocking)
        {
            Serial.println("Detected press - turn relay ON.");
          // enable relay output on valid debounced microswitch press)
          digitalWrite(RELAY, HIGH);
        }
    
    
         if (button.getSingleDebouncedRelease())      // check for debounced button press (not - blocking)
        {
            Serial.println("Detected release - turn relay OFF");
          // enable relay output on valid debounced microswitch release)
          digitalWrite(RELAY, LOW);
        }
    }
}
