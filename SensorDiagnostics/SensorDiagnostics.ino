/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int LeftValue = analogRead(A0);
  // print out the value you read:
 // Serial.print (" Left = ");
  Serial.println (LeftValue);
  //Average n readings of this sensor
 /* float totalValue = 0;
  int n = 20;
  unsigned long timeBefore = millis();
  for(int i=0; i<(n-1); i++)
  {
    LeftValue = analogRead(A0);
    totalValue = totalValue + LeftValue;
  }
  float avgLeftValue = totalValue/n;
  unsigned long timeAfter = millis();
  float timeToRun = (timeAfter - timeBefore);
  Serial.print (" Time to calculate is ");
  Serial.println (timeToRun);
 
  
  //Right
  int RightValue = analogRead(A4);
  Serial.print (" Right = ");
  Serial.print (RightValue);
  //Up
  int UpValue = analogRead(A1);
  Serial.print (" Up = ");
  Serial.print (UpValue);
  //Down
  int DownValue = analogRead(A3);
  Serial.print (" Down = ");
  Serial.print (DownValue);
  //Forward
  int ForwardValue = analogRead(A2);
  Serial.print (" Forward = ");
  Serial.print (ForwardValue);
  //Backward
  int BackwardValue = analogRead(A5);
  Serial.print (" Backward = ");
  Serial.print (BackwardValue);
  Serial.println (" ");
  Serial.print ("Average Left Value is ");
  Serial.println (avgLeftValue);
  */
  delay(50);        // delay in between reads for stability
}
