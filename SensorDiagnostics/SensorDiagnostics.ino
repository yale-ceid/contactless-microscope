/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

#define posYPin A2 //+y     high: 977     low: 59
#define negYPin A0 //-y     high: 968     low: 77
#define posXPin A4 //+x     high: 958     low: 71
#define negXPin A5 //-x     high: 954     low: 83
#define posZPin A1 //+z     high: 1008    low: 64
#define negZPin A3 //-z     high: 950     low: 97

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}
int diff = 20;
int zDiff = 120;

int posY0 = 0;
int negY0 = 0;
int posX0 = 0;
int negX0 = 0;
int posZ0 = 0;
int negZ0 = 0;
// the loop routine runs over and over again forever:
void loop() {
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
  Serial.print ("posY0 is ");
  Serial.print (posY0);
  Serial.print (".  negY0 is ");
  Serial.print (negY0);
  Serial.print (".  posX0 is ");
  Serial.print (posX0);
  Serial.print (".  negX0 is ");
  Serial.print (negX0);
  Serial.print (".  posZ0 is ");
  Serial.print (posZ0);
  Serial.print (".  negZ0 is ");
  Serial.println (negZ0);
  
  delay(50);        // delay in between reads for stability
}
