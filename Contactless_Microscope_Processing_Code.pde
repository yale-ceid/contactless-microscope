import processing.video.*;

Capture video;

int n = 0;

int timedelay = 0;

boolean dummy = false;

int w = displayWidth;

int h = displayHeight;

import processing.serial.*;

String val;

Serial myPort;

void setup() {

  size (displayWidth, displayHeight);

  printArray(Capture.list());

  video = new Capture(this, displayWidth, displayHeight,"Digital Microscope");

  video.start();
  
  String portName = Serial.list()[0];

  myPort = new Serial(this, portName, 115200);

}

void captureEvent (Capture video) {

 video.read();

}



void draw() {

  background (0);

  image(video,0,0);
  
  
  if (myPort.available() > 0) {

  if( (val = myPort.readStringUntil(ENTER)) != null) {val = trim(val);}   

  }

  else return;

  if (val != null) {

    println(val);

}

  if ("0".equals(val)) {

        image(video,0,0);

        save("image.png" + n);

        n = n+1;

        abcde();

        println("win");

       

        

  } 


      if(dummy) {

      delay(1000);

      background(0);

   textSize(70);

   fill(160);

  text("Your Image Number Is " + n, 1000/2, 1000/2);

    if (timedelay + 2000 < millis()){

  dummy = false;

    }

  }
}

void abcde() {

  //delay(1000);

  save(n + "image.png");

  timedelay = millis();

  dummy = true;

}
