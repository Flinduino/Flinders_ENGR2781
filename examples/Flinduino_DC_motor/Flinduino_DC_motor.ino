#include <SoftPWMServo.h> // pwm for speed control

//pin definitions
const int DC_DIR = 8;
const int DC_PWM = 9;

void setup() 
{
  // start the serial port (USB) to provide information about what is happening
  Serial.begin(115200);
  delay(3000);  

  //configure DC motor pins as outputs
  pinMode(DC_DIR, OUTPUT);
  pinMode(DC_PWM, OUTPUT);
  
  // write locic low (0v) to the motor to ensure that it is stoped
  digitalWrite(DC_PWM, LOW);    

  Serial.println("setup complete, starting main loop");
}

void loop() 
{
  // this disconnects the DC_PWM and DC_DIR pins from the PWM library so it can be used with digitalWrite()
  // it is only need in this demo as it swaps between modes of writing to the pin (SoftPWMServoPWMWrite and digitalWrite)
  SoftPWMServoPinDisable(DC_PWM);   
  SoftPWMServoPinDisable(DC_DIR);   
  delay(100);
  

  
    
  // full speed forward
  Serial.println("Full Speed positive direction (1 sec)");
  digitalWrite(DC_DIR, HIGH);   // set direction of rotation
  digitalWrite(DC_PWM, HIGH);   // logic high = full speed
  delay(1000);                  // run for 1 second


  // stop
  Serial.println("Stop (1 sec)");
  // write locic low (0v) to the motor to ensure that it is stoped
  digitalWrite(DC_PWM, LOW);    
  delay(1000);


  // full speed reverse
  Serial.println("Full Speed reverse direction (1 sec)");
  digitalWrite(DC_DIR, LOW);    // set direction of rotation
  digitalWrite(DC_PWM, HIGH);   // logic high = full speed
  delay(1000);                  // run for 1 second


  // stop
  Serial.println("Stop (1 sec)");
  // write locic low (0v) to the motor to ensure that it is stoped
  digitalWrite(DC_PWM, LOW);    
  delay(1000);



  //use pwm output to vary the speed of the motor
  //SoftPWMServoPWMWrite will vary the duty cycle: between 0 (always off) and 255 (always on). 
  
  // ramp speed from 0 - 100 %
  Serial.println("ramp speed from 0% - 100%"); 
  digitalWrite(DC_DIR, HIGH);   // set direction of rotation
  
  for (int i = 0; i < 255; i+=10)
  {     
    SoftPWMServoPWMWrite(DC_PWM, i);  // use i as the variable speed to send to the motor
    Serial.print("speed: ");
    Serial.println(i);
    delay (200);                       // wait for 20ms between changing to the next speed
  }

  Serial.println("wait 1 sec");
  delay(1000);



  Serial.println("ramp speed from 100% - 0%");
  for (int i = 255; i > 0; i-=10)
  {     
    SoftPWMServoPWMWrite(DC_PWM, i);  // use i as the variable speed to send to the motor
    Serial.print("speed: ");
    Serial.println(i);
    delay (200);                       // wait for 20ms between changing to the next speed
  }

  
  // stop
  Serial.println("Stop (1 sec)");
  // write locic low (0v) to the motor to ensure that it is stoped
  digitalWrite(DC_PWM, LOW);    
  delay(1000);
  

}
