#include <SoftPWMServo.h>

// Pin definitions
const int SERVO_PWM = 11;

//servo position list - setpoint in microseconds
const int servoPosition1 = 1000;
const int servoPosition2 = 1500;
const int servoPosition3 = 2000;



void setup() 
{
  // start the serial port (USB) to provide information about what is happening
  Serial.begin(115200);
  delay(3000);  

  
  pinMode(SERVO_PWM, OUTPUT);
  digitalWrite(SERVO_PWM, LOW);

  
  Serial.println("setup complete, starting main loop"); 
  Serial.println("Servo Testing");
}



void loop() 
{
   Serial.println("moving to predefined servo position - 'servoPosition1'");
  delay(50);
  Serial.println("... in 3 ...");
  delay(1000);
  Serial.println("... 2 ....");
  delay(1000);
  Serial.println("... 1 ...");
  delay(1000);
   SoftPWMServoServoWrite(SERVO_PWM, servoPosition1);
  Serial.println("... done");
  Serial.println();




  delay(1000);  // delay before next position


  

   Serial.println("moving to predefined servo position - 'servoPosition2'");
  delay(50);
  Serial.println("... in 3 ...");
  delay(1000);
  Serial.println("... 2 ....");
  delay(1000);
  Serial.println("... 1 ...");
  delay(1000);
   SoftPWMServoServoWrite(SERVO_PWM, servoPosition2);
  Serial.println("... done");
  Serial.println();



  delay(1000);  // delay before next position

  
  
  Serial.println("moving to predefined servo position - 'servoPosition3'");
  delay(50);
  Serial.println("... in 3 ...");
  delay(1000);
  Serial.println("... 2 ....");
  delay(1000);
  Serial.println("... 1 ...");
  delay(1000);
   SoftPWMServoServoWrite(SERVO_PWM, servoPosition3);
  Serial.println("... done");
  Serial.println();




  delay(1000);  // delay before going beack the other way
}
