import processing.serial.*;

Serial myPort;
//String inString;
//Switch to new String[3]; when adding z axis
//
String[] coordinates = new String[2];
PImage Butterfly;
PImage Leaf;
PImage Flower;
PImage Bee;
PImage CheckMark;
PImage Scroll;
PImage Letter;
PImage Forest;


String[] fontList = PFont.list();



float X;
float Y;
//float Z;
float xCoordinate;
float yCoordinate;
//float zCoordinate;
//float CircleX = 30;
//float CircleY = 30;

int gameScreen = 0;

float CounterButterfly = 0;
float CounterLeaf = 0;
float CounterFlower = 0;
float CounterBee = 0;

void setup()
{
  size(1102, 950);
  PFont font;
  font = loadFont("CooperBlack-48.vlw");
  textFont(font);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 115200);
 Butterfly = loadImage("Butterfly.png");
 Leaf = loadImage("Leaf.png");
 Flower = loadImage("Flower.png");
 Bee = loadImage("Bee.png");
 CheckMark = loadImage("CheckMark.png");
 Scroll = loadImage("Scroll.png");
 Letter = loadImage("Letter.png");
 Forest = loadImage("Forest.jpg");
 
}

void draw(){
  
  //printArray(fontList);
  
  if (gameScreen == 0){
    WelcomeScreen();
  } else if (gameScreen == 1){
    LetterScreen();
  } else if (gameScreen == 2){
    GameScreen();
  }
}

void WelcomeScreen(){
  background(0);
  fill(255);
  rect(300, 200, 450, 200);
  fill(0);
  textSize(32);
  image(Forest, 0, 0, 1300, 1300);
  text("Welcome to Arborset Forest,", 305, 225);
  text("a magical place that is home", 305, 265);
  text("to every insect and plant", 305, 305);
  text("found on Earth!", 305, 345);
  image(Scroll, 475, 600, 60, 60);
   fill(255);
  //ellipse(480, 610, 15, 15);
  //ellipse(530, 660, 15, 15);
  //ellipse(485, 645, 15, 15);
  //ellipse(525, 620, 15, 15);
}


void LetterScreen(){
  background(0);
  image(Letter, 251, 125, 600, 600);
  fill(0);
  text("Greetings Doctor,", 300, 270);
  text("We have an urgent matter, and", 300, 370);
  text("we need your help...", 300, 425);
  fill(0, 255, 0);
  rect(446, 800, 180, 80, 12, 12, 12, 12);
  fill(0);  
  text("Start", 500, 835); 
  text("Searching!", 460, 870); 
}


void GameScreen(){
  background(0);
  fill(255);
  rect(300, 150, 750, 700);
  rect(50, 300, 200, 400, 12, 12, 12, 12);
  image(Butterfly, 75, 325, 60, 60);
  image(Leaf, 75, 425, 60, 60);
  image(Flower, 75, 525, 60, 60);
  image(Bee, 75, 625, 60, 60);
  image(Butterfly, 500, 600, 60, 60);
  image(Leaf, 750, 200, 60, 60);
  image(Flower, 350, 300, 60, 60);
  image(Bee, 900, 700, 60, 60);
  fill(0);
  ellipse(X, Y, 30, 30);
 
//Butterfly
if ((X < 555) && (X > 500) && (Y < 650) && (Y > 605) && (CounterButterfly == 0)){
  image(CheckMark, 150, 325, 60, 60);
  CounterButterfly = CounterButterfly + 1;
}

if (CounterButterfly == 1){
  image(CheckMark, 150, 325, 60, 60);
}

//Leaf
if ((X < 805) && (X > 758) && (Y < 255) && (Y > 205) && (CounterLeaf == 0)){
  image(CheckMark, 150, 425, 60, 60);
  CounterLeaf = CounterLeaf + 1;
}

if (CounterLeaf == 1){
  image(CheckMark, 150, 425, 60, 60);
}

//Flower
if ((X < 410) && (X > 350) && (Y < 360) && (Y > 300) && (CounterFlower == 0)){
  image(CheckMark, 150, 525, 60, 60);
  CounterFlower = CounterFlower + 1;
}

if (CounterFlower == 1){
    image(CheckMark, 150, 525, 60, 60);
}

//Bee
if ((X < 950) && (X > 910) && (Y < 750) && (Y > 710) && (CounterBee == 0)){
  image(CheckMark, 150, 625, 60, 60);
  CounterBee = CounterBee + 1;
}

if (CounterBee == 1){
    image(CheckMark, 150, 625, 60, 60);
}
  
//  print("hi");
  if (coordinates.length != 2 || coordinates[0] == null || coordinates[1] == null){
   
    return;
  }
    print(coordinates[0]);
    print ("   ");
    println(coordinates[1]);
  xCoordinate = float(coordinates[0]);
  yCoordinate = float(coordinates[1]);
  //zCoordinate = float(coordinates[2]);
  
  
  
  X = map(xCoordinate, -1, 1101, 1046, 230);
  Y = map(yCoordinate, -1, 1051, 150, 850);
  
  
  //print(X);
  //println(Y);
  
}

void mouseClicked(){
  if ((mouseX < 530) && (mouseX > 480) && (mouseY < 655) && (mouseY > 610) && (gameScreen == 0)){
    startGame();
  }
}

void startGame(){
  gameScreen = 1;
}

void mousePressed(){
  if ((mouseX < 626) && (mouseX > 446) && (mouseY < 880) && (mouseY > 800) && (gameScreen == 1)){
    findObjects();
  }
}

void findObjects(){
  gameScreen = 2;
}
  
  
void serialEvent(Serial myPort)
{
  String inString = myPort.readStringUntil('\n');
  if (inString !=null)
  {
    inString = trim(inString);
    //String[] list = split(inString, ',');
    //print(list[0]);
    //print(list[1]);
    //print(inString);
    
    coordinates = split(inString, ',');
  }
  
  //print(list[0]);
  //print(list[1]);
//  print(coordinates);
  //print(coordinates[0]);
  //print ("   ");
  //println(coordinates[1]);
  
}
