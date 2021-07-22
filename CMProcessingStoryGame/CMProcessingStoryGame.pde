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
PImage Bubble;
PImage Grass;
//PImage Bush;


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

PFont font;
PFont letterfont;
PFont gamefont;

void setup()
{
  size(1102, 950);

  font = loadFont("CooperBlack-48.vlw");
  letterfont = loadFont("VinerHandITC-48.vlw");
  gamefont = loadFont("CourierNewPS-BoldMT-48.vlw");
  
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
 Bubble = loadImage("Bubble.png");
 Grass = loadImage("Grass.jpg");
 //Bush = loadImage("Bush.png");
 
}

void draw(){
  
  //printArray(fontList);
  
  if (gameScreen == 0){
    WelcomeScreen();
  } else if (gameScreen == 1){
    LetterScreen();
  } else if (gameScreen == 2){
    GameScreen();
  } else if (gameScreen == 3){
    EndScreen();
  }
}

void WelcomeScreen(){
  background(0);
  textFont(font);
  fill(0);
  textSize(32);
  image(Forest, 0, 0, 1300, 1300);
  fill(255, 255, 0);
  rect(300, 200, 450, 200, 12, 12, 12, 12);
  fill(0); 
  text("Welcome to Arborset", 350, 230);
  text("Forest, a magical place", 336, 268);
  text("that is home to every", 343, 307);
  text("insect and plant found", 336, 345);
  text("on Earth!", 430, 385);
  image(Scroll, 80, 800, 90, 90);
  image(Bubble, 200, 600, 205, 205);
  fill(255, 0, 0);
  text("Urgent!", 223, 678);
   fill(255);
  //ellipse(90, 810, 15, 15);
  //ellipse(165, 880, 15, 15);
  //ellipse(100, 875, 15, 15);
  //ellipse(160, 830, 15, 15);
}


void LetterScreen(){
  background(0);
  image(Letter, 251, 125, 600, 600);
  fill(0);  
  textFont(letterfont); 
  textSize(32);
  text("Greetings Doctor,", 300, 210);
  text("We have an urgent matter, and", 300, 300);
  text("we need your help! A virus has", 300, 345);
  text("been detected within some of the", 300, 390);
  text("living things in Arborset. We", 300, 435);
  text("need you to collect samples and", 300, 480);
  text("study the infected plants and", 300, 525);
  text("insects. Good luck Doctor and be", 300, 570);
  text("quick, the virus is spreading", 305, 615);
  text("rapidly!", 310, 660);
  fill(0, 255, 0);
  rect(446, 800, 180, 80, 12, 12, 12, 12);
  fill(0); 
  textFont(font);
  textSize(30);
  text("Start", 500, 830); 
  text("Searching!", 460, 865); 
}


void GameScreen(){
  background(0);
  background(173, 216, 230);
  fill(255);
  //rect(300, 150, 750, 700);
  image(Grass, 300, 150, 750, 700);
  //image(Bush, 300, 150, 350, 200);
  fill(195, 155, 119);
  rect(50, 235, 200, 100, 12, 12, 12, 12); 
  rect(50, 360, 200, 400, 12, 12, 12, 12);
  textFont(gamefont);
  fill(0);
  textSize(38);
  text("Field", 90, 275);
  text("Guide", 91, 315);
  image(Butterfly, 75, 385, 60, 60);
  image(Leaf, 75, 485, 60, 60);
  image(Flower, 75, 585, 60, 60);
  image(Bee, 75, 685, 60, 60);
  image(Butterfly, 500, 600, 60, 60);
  image(Leaf, 750, 200, 60, 60);
  image(Flower, 350, 300, 60, 60);
  image(Bee, 900, 700, 60, 60);
  fill(0);
  ellipse(X, Y, 30, 30);
 
//Butterfly
if ((X < 555) && (X > 500) && (Y < 650) && (Y > 605) && (CounterButterfly == 0)){
  image(CheckMark, 150, 385, 60, 60);
  CounterButterfly = CounterButterfly + 1;
}

if (CounterButterfly == 1){
  image(CheckMark, 150, 385, 60, 60);
}

//Leaf
if ((X < 805) && (X > 758) && (Y < 255) && (Y > 205) && (CounterLeaf == 0)){
  image(CheckMark, 150, 485, 60, 60);
  CounterLeaf = CounterLeaf + 1;
}

if (CounterLeaf == 1){
  image(CheckMark, 150, 485, 60, 60);
}

//Flower
if ((X < 410) && (X > 350) && (Y < 360) && (Y > 300) && (CounterFlower == 0)){
  image(CheckMark, 150, 585, 60, 60);
  CounterFlower = CounterFlower + 1;
}

if (CounterFlower == 1){
    image(CheckMark, 150, 585, 60, 60);
}

//Bee
if ((X < 950) && (X > 910) && (Y < 750) && (Y > 710) && (CounterBee == 0)){
  image(CheckMark, 150, 685, 60, 60);
  CounterBee = CounterBee + 1;
}

if (CounterBee == 1){
    image(CheckMark, 150, 685, 60, 60);
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
  
  
  
  X = map(xCoordinate, -1, 958, 1046, 304);
  Y = map(yCoordinate, 179, 1051, 850, 150);
  //Original
  //X = map(xCoordinate, -1, 1101, 1046, 230);
  //Y = map(yCoordinate, -1, 1051, 150, 850);
  
  
  //print(X);
  //println(Y);
  
  if ((CounterButterfly == 1) && (CounterLeaf == 1) && (CounterFlower == 1) && (CounterBee == 1)){
    Ending();
  }
  
}

void EndScreen(){
  background(0);
  background(173, 216, 230);
  fill(255, 119, 255);
  rect(201, 275, 700, 240);
  textFont(font);
  fill(0);
  text("Congratulations!", 328, 330);
  text("You collected everything", 230, 400);
  text("and cured the virus!", 285, 470);
}
  

void mouseClicked(){
  if ((mouseX < 165) && (mouseX > 90) && (mouseY < 880) && (mouseY > 810) && (gameScreen == 0)){
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
  //if ((CounterButterfly == 1) && (CounterLeaf == 1) && (CounterFlower == 1) && (CounterBee == 1)){
  //  Ending();
  //}
}

void Ending(){
  gameScreen = 3;
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
