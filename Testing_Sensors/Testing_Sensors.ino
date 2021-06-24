#include <Stepper.h>

#define posYPin A4 //+y     high: 977     low: 59
#define negYPin A5 //-y     high: 968     low: 77
#define posXPin A0 //+x     high: 958     low: 71
#define negXPin A2 //-x     high: 954     low: 83
#define posZPin A3 //+z     high: 1008    low: 64
#define negZPin A1 //-z     high: 950     low: 97

const int steps = 200; //number of steps in one revolution

float posY0 = 860;
float negY0 = 860;
float posX0 = 860;
float negX0 = 860;
float posZ0 = 860;
float negZ0 = 860;

float diff = 20;
float zDiff = 40;

Stepper myStepperZ(steps, 28, 27, 29, 30);
Stepper myStepperX(steps, 18, 17, 19, 20);
Stepper myStepperY(steps, 22, 23, 24, 25);

int CounterX = 0;
int CounterY = 0;
int CounterZ = 0;

//Pedal Setup
const int pushButtonPin = 7;           // the number of the pushbutton pin
const int pushButtonDebounceDelay = 50; // the debounce time; increase if the output flickers

// Variables will change:
int lastSteadyState = LOW;      // the previous steady state from the input pin
int lastFlickerableState = LOW; // the previous flickerable state from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled

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
  pinMode(pushButtonPin, INPUT_PULLUP);
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
    myStepperY.step(-1);
    delay(5);
  }
  //Serial.println("Y is homed");
  pinMode(homeSwitchZ, INPUT_PULLUP);
  while (switchZ == LOW)
  {
    switchZ = digitalRead(homeSwitchZ);
    myStepperZ.step(1);
    delay(5);
  }
  //Serial.println("Z is homed");

    int centerCounter = 0;
  while (centerCounter<550){
    myStepperZ.step(-1);
    myStepperY.step(1);
    myStepperX.step(1);
    delay(2);
    centerCounter++;
    CounterX++;
    CounterY++;
    CounterZ++;
  }

  posY0 = -diff + analogRead(posYPin); //move in the + direction
  negY0 = -diff + analogRead(negYPin); //move in the - direction
  posX0 = -diff + analogRead(posXPin);
  negX0 = -diff + analogRead(negXPin);
  posZ0 = -zDiff + analogRead(posZPin); //move in the + direction
  negZ0 = -zDiff + analogRead(negZPin); //move in the - direction
}

void loop()
{
 // pushButton();
  moveYAxis();
 // moveXAxis();
//  moveZAxis();
}

void pushButton()
{
  int pushButtonState = digitalRead(pushButtonPin);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch/button changed, due to noise or pressing:
  if (pushButtonState != lastFlickerableState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = pushButtonState;
  }

  if ((millis() - lastDebounceTime) > pushButtonDebounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (lastSteadyState == HIGH && pushButtonState == LOW)
      Serial.println("0");
    else if (lastSteadyState == LOW && pushButtonState == HIGH)
      Serial.println("1");

    // save the the last steady state
    lastSteadyState = pushButtonState;
  }
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
    long int posYDelay = (1000000 / (10 + posY0 - posYRead));
    timeMicros = posYDelay % 1000;
    timeMillis = posYDelay / 1000;
    CounterY = CounterY + 1;
  }

  // Y-
  else if ((posYRead >= posY0) && (negYRead <= negY0) && (CounterY >= 0))
  {
    myStepperY.step(-1);
    long int negYDelay = (1000000 / (10 + negY0 - negYRead));
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
    myStepperX.step(-1);
    long int negXDelay = (1000000 / (10 + posX0 - posXRead));
    timeMicros = negXDelay % 1000;
    timeMillis = negXDelay / 1000;
    CounterX = CounterX - 1;
  }

  // X-
  else if ((negXRead <= negX0) && (posXRead >= posX0) && (CounterX <= 1000))
  {

    myStepperX.step(1);
    long int posXDelay = (1000000 / (10 + negX0 - negXRead));
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
  if ((posZRead <= posZ0) && (negZRead >= negZ0) && (CounterZ >= 0))
  {
    myStepperZ.step(1);
    long int posZDelay = (1000000 / (10 + posZ0 - posZRead));
    timeMicros = posZDelay % 1000;
    timeMillis = posZDelay / 1000;
    CounterZ = CounterZ - 1;
  }

  // Z-
  else if ((posZRead >= posZ0) && (negZRead <= negZ0) && (CounterZ <= 4000))
  {
    myStepperZ.step(-1);
    long int negZDelay = (1000000 / (10 + negZ0 - negZRead));
    timeMicros = negZDelay % 1000;
    timeMillis = negZDelay / 1000;
    CounterZ = CounterZ + 1;
  }

  if (timeMicros || timeMillis)
  {
    delay(timeMillis);
    delayMicroseconds(timeMicros);
  }
}
