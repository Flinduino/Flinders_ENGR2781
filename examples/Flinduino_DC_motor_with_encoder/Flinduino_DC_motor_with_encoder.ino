#include <SoftPWMServo.h> // pwm for speed control

// pin defintions
const int ENC_A_PIN = 2;     //C2    
const int ENC_B_PIN = 3;    //C3

const int DC_DIR = 8;
const int DC_PWM = 9;

// encoder configuration
long encCount = 0;                        // main variable to store the encoder count value

bool encA_prevState;                      // variables tostore the previous and current pin states
bool encB_prevState;
bool encA_curState;
bool encB_curState;

void __USER_ISR  changeNotificationISR();   // function prototype for the pin change notification interupt
void processEncoder();                      // function prototype called by the interupt to process the encoder pins


int countsToMove = 28734;                // how many encoder counts to move the motor


void setup() 
{
  // start the serial port (USB) to provide information about what is happening
  Serial.begin(115200);
  delay(3000);  

  // setup encoder
  //--------------
  //configure encoder pins as inputs (with pullup resistors)
  pinMode(ENC_A_PIN, INPUT_PULLUP);
  pinMode(ENC_B_PIN, INPUT_PULLUP);


  //configure the flinduino registers correctly for enabling interupts
  //change notification port PIN on port enable 
  CNENCSET = CNENCSET | (1 << 2); //RC2
  CNENCSET = CNENCSET | (1 << 3); //RC3
  
  //change notification configuration (turn on)
  CNCONCSET = CNCONCSET | (1 << 15);


  //clear interupt flags
  clearIntFlag(_CHANGE_NOTICE_C_IRQ);
  
  // set the function to be called
  setIntVector(_CHANGE_NOTICE_VECTOR, changeNotificationISR);

  // enable change notification interups
  setIntEnable(_CHANGE_NOTICE_C_IRQ);


  //set the priority of the interupt
  setIntPriority(_CHANGE_NOTICE_VECTOR, 4, 0);


  // setup dc motor
  //---------------
  //configure DC motor pins as outputs
  pinMode(DC_DIR, OUTPUT);
  pinMode(DC_PWM, OUTPUT);

  // write locic low (0v) to the motor to ensure that it is stoped
  digitalWrite(DC_PWM, LOW);   


  
  Serial.println("setup complete, starting main loop");
}



void loop() 
{
  Serial.print("Program will drive DC motor until step count is >= ");
  Serial.println(countsToMove);
  delay(500);
  Serial.println("Starting in 3...");
  delay(1000);
  Serial.println("Starting in 2...");
  delay(1000);
  Serial.println("Starting in 1...");
  delay(1000);
  
    

  digitalWrite(DC_DIR, HIGH);   // set direction of rotation


  // ramp up speed
  for (int i = 0; i < 255; i++)
  { 
    // print speed, current encoder value and how many remain (put common/ repeated code in a function)
    printDetails(i, encCount);          

    // check to see if reached target
    if(encCount >= countsToMove) break; // jump out the loop
     
    SoftPWMServoPWMWrite(DC_PWM, i);   // use i as the variable speed to send to the motor
    delay (20);                       // wait for 20ms between changing to the next speed
                                      // dont wait too long or might not check encoder count quickly enough
  }

  // maintain speed until target met
  while( encCount <= countsToMove)
  {
    printDetails(255, encCount);
    delay(20);                        // dont wait too long or might not check encoder count quickly enough
  }

  // reached target
  Serial.println("reached target");
  // stop the motor
   SoftPWMServoPWMWrite(DC_PWM, 0); 


  while(true)   // will stay in this loop forever because true is always true.
  { 
    Serial.print("done, ");
    printDetails(0,encCount);
    delay(500);
  }
  


}




//-----------------------------------------------------------------------------------
// prints the set speed, current encoder value and how many encoder counts remain
// It is good practice to put common / repeated code in its own function to help reduce clutter
//-----------------------------------------------------------------------------------
void printDetails(int _setSpeed, long _encCount)
{
  Serial.print("set speed: ");
  Serial.print(_setSpeed);
  Serial.print(", enc: ");
  Serial.print(_encCount);
  Serial.print(", remain: ");
  Serial.println(countsToMove - _encCount);   

}


//-----------------------------------------------------------------------------------
// implementation of the the change notification interrupt routine for the encoder
//-----------------------------------------------------------------------------------
void __USER_ISR  changeNotificationISR()
{
  processEncoder();     // do the counting
  
  // clear the interupt flags
  clearIntFlag(_CHANGE_NOTICE_C_IRQ );    

}



//-----------------------------------------------------------------------------------
// process encoder function implementation
//
// implements x4 configuration of an AB encoder
//       - this increments or decrements the encoder count variable 
//         on the rising and falling edge of both pins (A and B) of the encoder
//         https://www.dynapar.com/technology/encoder_basics/quadrature_encoder/
//-----------------------------------------------------------------------------------
void processEncoder()
{
  encA_curState = PORTCbits.RC2;
  encB_curState =   PORTCbits.RC3;

  //if A was the pin that changed
  if (encA_curState != encA_prevState)
  {
    if (encA_prevState == LOW)
    { //rising edge
      if (encB_curState == HIGH)
      {
        encCount++;
      }
      else
      {
        encCount--;
      }
    }
    else
    { //falling edge
      if (encB_curState == LOW)
      {
        encCount++;
      }
      else
      {
        encCount--;
      }
    }
    encA_prevState = encA_curState;
  }

  
  //if B was the pin that changed
  else
  {
    if (encB_prevState == LOW)
    { //rising edge
      if (encA_curState == LOW)
      {
        encCount++;
      }
      else
      {
        encCount--;
      }
    }
    else
    { //falling edge
      if (encA_curState == HIGH)
      {
        encCount++;
      }
      else
      {
        encCount--;
      }
    }

    encB_prevState = encB_curState;
  }
}
