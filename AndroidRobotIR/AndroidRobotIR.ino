#include <Servo.h>

Servo LeftServo;
Servo RightServo;

int StopValue = 1500;
int ClockWise = 1300;
int CounterClockWise = 1700;

void setup()
{
  LeftServo.attach(9);
  RightServo.attach(10);
  Serial.begin(9600);
  Serial.println("ready");
}

void loop()
{
  while (Serial.available()) {
    TakeAction(Serial.readStringUntil('\n'));
  }
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

void TurnRight()
{
  Serial.println("right");
  LeftServo.writeMicroseconds(CounterClockWise);
  RightServo.writeMicroseconds(CounterClockWise);
}


void TurnLelf()
{
  Serial.println("left");
  LeftServo.writeMicroseconds(ClockWise);
  RightServo.writeMicroseconds(ClockWise);
}

void StopAction()
{
  Serial.println("stop");
  LeftServo.writeMicroseconds(StopValue);
  RightServo.writeMicroseconds(StopValue);
}



