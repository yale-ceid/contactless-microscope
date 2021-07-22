#include <Stepper.h>

#define posYPin A2 //+y     high: 977     low: 59
#define negYPin A0 //-y     high: 968     low: 77
#define posXPin A4 //+x     high: 958     low: 71
#define negXPin A5 //-x     high: 954     low: 83
#define posZPin A1 //+z     high: 1008    low: 64
#define negZPin A3 //-z     high: 950     low: 97

const int steps = 200; //number of steps in one revolution

float posY0 = 860;
float negY0 = 860;
float posX0 = 860;
float negX0 = 860;
float posZ0 = 0;
float negZ0 = 0;

float diff = 20;
float zDiff = 120;

Stepper myStepperZ(steps, 27, 28, 29, 30);
Stepper myStepperX(steps, 22, 23, 25, 24);
Stepper myStepperY(steps, 17, 18, 19, 20);

int CounterX = 0;
int CounterY = 0;
int CounterZ = 0;

//Limit Switch Setup
int switchX;
int switchY;
int switchZ;
int homeSwitchX = 42;
int homeSwitchY = 43;
int homeSwitchZ = 44;

void setup()
{
  // set motor speed at 60 rpm:
  myStepperZ.setSpeed(60);
  myStepperY.setSpeed(60);
  myStepperX.setSpeed(60);
  // initialize the serial port:
  Serial.begin(115200);
  pinMode(homeSwitchX, INPUT_PULLUP);
  while (switchX == LOW)
  {
    switchX = digitalRead(homeSwitchX);
    myStepperX.step(-1);
    delay(5);
  }
  //Serial.println("X is homed");
  pinMode(homeSwitchY, INPUT_PULLUP);
  while (switchY == LOW)
  {
    switchY = digitalRead(homeSwitchY);
    myStepperY.step(-1); //maybe -1
    delay(5);
  }
  //Serial.println("Y is homed");
  pinMode(homeSwitchZ, INPUT_PULLUP);
  while (switchZ == LOW)
  {
    switchZ = digitalRead(homeSwitchZ);
    myStepperZ.step(-1);
    delay(5);
  }
  //Serial.println("Z is homed");

    int centerCounter = 0;
  while (centerCounter<550){
    myStepperZ.step(1);
    myStepperY.step(1);
    myStepperX.step(1);
    delay(2);
    centerCounter++;
    CounterX++;
    CounterY++;
    CounterZ++;
  }

  //Average n readings of all sensors
  float totalForwardValue = 0;
  float totalBackwardValue = 0;
  float totalLeftValue = 0;
  float totalRightValue = 0;
  float totalUpValue = 0;
  float totalDownValue = 0;
  int ForwardValue;
  int BackwardValue;
  int LeftValue;
  int RightValue;
  int UpValue;
  int DownValue;
  
  int n = 100;
  for(int i=0; i<(n-1); i++)
  {
    //Forward
    ForwardValue = analogRead(posYPin);
    totalForwardValue = totalForwardValue + ForwardValue;
    //Forward
    BackwardValue = analogRead(negYPin);
    totalBackwardValue = totalBackwardValue + BackwardValue;
    //Left
    LeftValue = analogRead(negXPin);
    totalLeftValue = totalLeftValue + LeftValue;
    //Right
    RightValue = analogRead(posXPin);
    totalRightValue = totalRightValue + RightValue;
    //Up
    UpValue = analogRead(posZPin);
    totalUpValue = totalUpValue + UpValue;
    //Down
    DownValue = analogRead(negZPin);
    totalDownValue = totalDownValue + DownValue;
  }
  float avgForwardValue = totalForwardValue/n;
  float avgBackwardValue = totalBackwardValue/n;
  float avgLeftValue = totalLeftValue/n;
  float avgRightValue = totalRightValue/n;
  float avgUpValue = totalUpValue/n;
  float avgDownValue = totalDownValue/n;
  

  //Set initial readings for each sensor
  posY0 = -diff + avgForwardValue; //move in the + direction
  negY0 = -diff + avgBackwardValue; //move in the - direction
  posX0 = -diff + avgRightValue;
  negX0 = -diff + avgLeftValue;
  posZ0 = -zDiff + avgUpValue; //move in the + direction
  negZ0 = -zDiff + avgDownValue; //move in the - direction
}

void loop()
{
  moveYAxis();
  moveXAxis();
  moveZAxis();
}

void moveYAxis()
{
  float posYRead = analogRead(posYPin);
  float negYRead = analogRead(negYPin);
//  Serial.println(negYRead);
  int timeMicros = 0;
  int timeMillis = 0;

  // Y+
  if ((posYRead <= posY0) && (negYRead >= negY0) && (CounterY <= 1050))
  {
    myStepperY.step(1);
    long int posYDelay = (6000000 / (10 + posY0 - posYRead));
    timeMicros = posYDelay % 1000;
    timeMillis = posYDelay / 1000;
    CounterY = CounterY + 1;
  }

  // Y-
  else if ((posYRead >= posY0) && (negYRead <= negY0) && (CounterY >= 0))
  {
    myStepperY.step(-1);
    long int negYDelay = (6000000 / (10 + negY0 - negYRead));
    timeMicros = negYDelay % 1000;
    timeMillis = negYDelay / 1000;
    CounterY = CounterY - 1;
  }

  if (timeMicros || timeMillis)
  {
    delay(timeMillis);
    delayMicroseconds(timeMicros);
  }
}

void moveXAxis()
{
  float posXRead = analogRead(posXPin);
  float negXRead = analogRead(negXPin);

  int timeMicros = 0;
  int timeMillis = 0;

  // X+
  if ((negXRead >= negX0) && (posXRead <= posX0) && (CounterX >= 0))
  {
    myStepperX.step(1);
    long int negXDelay = (7000000 / (10 + posX0 - posXRead));
    timeMicros = negXDelay % 1000;
    timeMillis = negXDelay / 1000;
    CounterX = CounterX - 1;
  }

  // X-
  else if ((negXRead <= negX0) && (posXRead >= posX0) && (CounterX <= 1000))
  {

    myStepperX.step(-1);
    long int posXDelay = (7000000 / (10 + negX0 - negXRead));
    timeMicros = posXDelay % 1000;
    timeMillis = posXDelay / 1000;
    CounterX = CounterX + 1;
  }

  if (timeMicros || timeMillis)
  {
    delay(timeMillis);
    delayMicroseconds(timeMicros);
  }
}

void moveZAxis()
{
  float posZRead = analogRead(posZPin); //move in the + direction
  float negZRead = analogRead(negZPin); //move in the - direction

  int timeMicros = 0;
  int timeMillis = 0;

  // Z+
  if ((posZRead <= posZ0) && (negZRead >= negZ0) && (CounterZ <= 2000))
  {
    myStepperZ.step(1);
    long int posZDelay = (4000000 / (10 + posZ0 - posZRead));
    timeMicros = posZDelay % 1000;
    timeMillis = posZDelay / 1000;
    CounterZ = CounterZ + 1;
  }

  // Z-
  else if ((posZRead >= posZ0) && (negZRead <= negZ0) && (CounterZ >= 0))
  {
    myStepperZ.step(-1);
    long int negZDelay = (4000000 / (10 + negZ0 - negZRead));
    timeMicros = negZDelay % 1000;
    timeMillis = negZDelay / 1000;
    CounterZ = CounterZ - 1;
  }

  if (timeMicros || timeMillis)
  {
    delay(timeMillis);
    delayMicroseconds(timeMicros);
  }
}
