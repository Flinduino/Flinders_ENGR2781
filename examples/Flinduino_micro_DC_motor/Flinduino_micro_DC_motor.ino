#include <SoftPWMServo.h>

// Pin definitions
const int MICRO_DC_PWM =10;




void setup() 
{
  // start the serial port (USB) to provide information about what is happening
  Serial.begin(115200);
  delay(3000);  

  // configure the micro motor pin as an output
  pinMode(MICRO_DC_PWM, OUTPUT);
    
  // write locic low (0v) to the motor to ensure that it is stoped
  digitalWrite(MICRO_DC_PWM, LOW);

  
  Serial.println("setup complete, starting main loop"); 
  Serial.println("micro DC motor testing");
  Serial.println("500us = Full Speed Forward");
  Serial.println("1400us - 1600us = Stop");
  Serial.println("2500us = Full Speed Backward");
}



void loop() 
{
  // use servo output to vary the speed of the micro dc motor
  //   500 microseconds = Full Speed Forward
  // 1500 microseconds = Sstop       (1400us - 1600us  deadband)
  // 2500 microseconds = Full Speed Backward

  
  // ramp speed from 0 - 100 %
  Serial.println("ramp speed from 0% - 100% (Forward)"); 

  for (int i = 1500; i >500; i-=50)
  {     
    SoftPWMServoServoWrite(MICRO_DC_PWM, i);  // use i as the variable speed to send to the motor
    Serial.print("speed (in us): ");
    Serial.println(i);
    delay (200);                       // wait for 20ms between changing to the next speed
  }
  


  Serial.println("wait 1 sec");
  delay(1000);


  Serial.println("ramp speed from 100% - 0%");
  for (int i = 500; i <1500; i+=50)
  {     
    SoftPWMServoServoWrite(MICRO_DC_PWM, i);  // use i as the variable speed to send to the motor
    Serial.print("speed (in us): ");
    Serial.println(i);
    delay (200);                       // wait for 20ms between changing to the next speed
  }

  
  // stop
  Serial.println("Stop (1 sec)");
   SoftPWMServoServoWrite(MICRO_DC_PWM, 1500);
  delay(1000);




//////////////////////////////


  // ramp speed from 0 - 100 %
  Serial.println("ramp speed from 0% - 100% (reverse)"); 

  for (int i = 1500; i <2500; i+=50)
  {     
    SoftPWMServoServoWrite(MICRO_DC_PWM, i);  // use i as the variable speed to send to the motor
    Serial.print("speed (in us): ");
    Serial.println(i);
    delay (200);                       // wait for 20ms between changing to the next speed
  }
  

  Serial.println("wait 1 sec");
  delay(1000);


  Serial.println("ramp speed from 100% - 0%");
  for (int i = 2500; i >1500; i-=50)
  {     
    SoftPWMServoServoWrite(MICRO_DC_PWM, i);  // use i as the variable speed to send to the motor
    Serial.print("speed (in us): ");
    Serial.println(i);
    delay (200);                       // wait for 20ms between changing to the next speed
  }

  
  // stop
  Serial.println("Stop (1 sec)");
   SoftPWMServoServoWrite(MICRO_DC_PWM, 1500);
  delay(1000);
  
}
