// pin defintions
const int ENC_A_PIN = 2;     //C2    
const int ENC_B_PIN = 3;    //C3

// encoder configuration
long encCount = 0;                        // main variable to store the encoder count value

bool encA_prevState;                      //variables tostore the previous and current pin states
bool encB_prevState;
bool encA_curState;
bool encB_curState;

void __USER_ISR  changeNotificationISR();   // function prototype for the pin change notification interupt
void processEncoder();                      // function prototype called by the interupt to process the encoder pins



void setup() 
{
  // start the serial port (USB) to provide information about what is happening
  Serial.begin(115200);
  delay(3000);  

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
  
  Serial.println("setup complete, starting main loop");

  Serial.println("Rotate the wheel with the encoder to see the value change");
}



void loop() 
{
  // note that as the counting is all done in an interrupt, 
  // you do not need to call any functions to get the encoder to work.
  // you can simple use the value.
  
  Serial.print("Encoder pulse count: ");
  Serial.println(encCount);
  delay(100); 
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
  encB_curState =  PORTCbits.RC3;

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
