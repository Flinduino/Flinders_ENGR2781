#include <Stepper.h>

// Pin definitions
const int STEPPER_PWM_A = 4;     
const int STEPPER_PWM_B = 5;     
const int STEPPER_DIR_A = 6;     
const int STEPPER_DIR_B = 7;    


// Stepper configuration
const int stepsPerRevolution = 400;
Stepper myStepper(stepsPerRevolution, STEPPER_DIR_B, STEPPER_DIR_A, STEPPER_PWM_B, STEPPER_PWM_A);      // create the stepper motor controller called "myStepper" with the required parameters



void setup() 
{
  // start the serial port (USB) to provide information about what is happening
  Serial.begin(115200);
  delay(2000);  
  Serial.println("setup complete, starting main loop");
}



void loop() 
{
  Serial.println("Rotate Stepper 1 full revolution");
  
  Serial.println("... setting speed to 60 RPM");
  myStepper.setSpeed(60);               //set the stepper motor speed to 60 RPM

  Serial.println("... start");
  myStepper.step(stepsPerRevolution);   // this function will block (wait here) untill all steps are done at the specified RPM
  Serial.println("... done");
  Serial.println();




  delay(1000);  // delay before going beack the other way




  Serial.println("Rotate Stepper 1/2 full revolution reverse");
  
  Serial.println("... setting speed to 120 RPM");
  myStepper.setSpeed(50);               //set the stepper motor speed to 60 RPM

  Serial.println("... start");
  myStepper.step(-stepsPerRevolution/2);   // this function will block (wait here) untill all steps are done at the specified RPM
  Serial.println("... done");
  Serial.println();
  

  delay(1000);  // delay before going beack the other way
}
