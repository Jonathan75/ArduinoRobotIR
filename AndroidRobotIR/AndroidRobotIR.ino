#include <Servo.h>
#include <IRremote.h>

Servo LeftServo;
Servo RightServo;

int StopValue = 1500;
int ClockWise = 1300;
int CounterClockWise = 1700;
IRrecv irrecv(9);
decode_results results;

void setup()
{
  irrecv.enableIRIn(); 
  pinMode(13, OUTPUT);
  LeftServo.attach(6);
  RightServo.attach(5);
  Serial.begin(9600);
  Serial.println("ready");
}

void loop()
{
  ReadIR();
  while (Serial.available()) {
    TakeAction(Serial.readStringUntil('\n'));
  }
  

}


void ReadIR()
{
  if (irrecv.decode(&results)) {
    Serial.println("IR recieved");
    Blink(true);
    Serial.println(results.value, HEX);
    storeCode(results.value);
    irrecv.resume();
    Blink(false);
  }
}

//void storeCode(decode_results *results) 
void storeCode(int results) 
{
  //results->value, HEX
  switch (results)
  {
    case 0xFDA05F:
      Forward();
      break;
    
    case 0xFD10EF:
      TurnLelf();
      break;
      
    case 0xFD50AF:
      TurnRight();
      break; 

    case 0xFDB04F:
      Back();
      break;       
      
    case 0xFD906F:
      StopAction();
      break; 
      
    
    default:
    break;
  }

}


void Blink(bool value)
{
  digitalWrite(13, value);
}

void TakeAction(String action)
{

  switch (action[0])
  {
    case 'l':
      TurnLelf();
      break;
    case 'r':
      TurnRight();
      break;
    case 's':
      StopAction();
      break;
    default:
      Serial.println("nothing");
  }
}

void Forward()
{
  Serial.println("forward");
  LeftServo.writeMicroseconds(ClockWise);
  RightServo.writeMicroseconds(CounterClockWise);
}

void Back()
{
  Serial.println("back");
  
  LeftServo.writeMicroseconds(CounterClockWise);
  RightServo.writeMicroseconds(ClockWise);
}

void TurnRight()
{
  Serial.println("right");
  LeftServo.writeMicroseconds(ClockWise);
  RightServo.writeMicroseconds(ClockWise);
}

void TurnLelf()
{
  Serial.println("left");
  LeftServo.writeMicroseconds(CounterClockWise);
  RightServo.writeMicroseconds(CounterClockWise);
}

void StopAction()
{
  Serial.println("stop");
  LeftServo.writeMicroseconds(StopValue);
  RightServo.writeMicroseconds(StopValue);
}



