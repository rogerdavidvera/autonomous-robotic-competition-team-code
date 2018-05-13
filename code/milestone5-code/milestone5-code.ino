/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 5 DEBUG VERSION
*************************************************************/

# include <Servo.h>
# include <SPI.h>
# include <Pixy.h>
# include <Adafruit_TCS34725.h>

// MISCELLANEOUS VARIABLES
int initialNum = 500;
int quadrant = 1;
int color = initialNum;
int caseNum = 1;

// MOTOR VARIABLES
int directionLeft = 13;
int directionRight = 12;
int brakeLeft = 8;
int brakeRight = 9;
int motorLeft = 11;
int motorRight = 3; 
int normalSpeed = 120;

// PIXY VARIABLES
Pixy pixy;
static int i = 0;
int j;
uint16_t blocks;
char buf[32];
int x = initialNum;
int y = initialNum;
int width = initialNum;
int height = initialNum;
int egg = initialNum;
int sig = initialNum;
int area = initialNum;
float h;
float w;
float ratioHW;

// RGB SENSOR VARIABLES
Adafruit_TCS34725 tcs = Adafruit_TCS34725
    (TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t clear, sum, red, green, blue;
float r, g, b;

// COLOR found boolean
int boundaryFound = 0;

// WHITE line hit boolean
int whiteLineFound = 0;

int grayMatCounter = 0;

// Egg found boolean
int eggFound = 0;

// IR SENSOR VARIABLES
//int irLED = 53;

// LED VARIABLES
int redLED = 2;
int orangeLED = 4;
int yellowLED = 5;
int greenLED = 6;

void setup() {

  Serial.begin(9600);
  Serial.println("Starting...");

  //setting up pixy cam
  pixy.init();
  Serial.println("Pixy set");
  //setting up rgb sensor
  tcs.begin();
  Serial.println("RGB set");
  //setting up left motor
  pinMode(directionLeft, OUTPUT);
  pinMode(brakeLeft, OUTPUT); 

  //setting up right motor
  pinMode(directionRight, OUTPUT); 
  pinMode(brakeRight, OUTPUT);  

  //setting up color LEDs
  pinMode(redLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  Serial.println("All things set");

}

void loop() {

  delay(1000);

  /* FIRST STATE OF PROGRAM*/
  /*
   * In this state, if a boundary has not been found. The boundaryFound
   * variable is still equal to 0. So as long as condition that boundaryFound
   * is not ZERO, the while loop will keep continuing.
   * 
   * Once, a boundary is found. The quadrant variable is set to the number
   * describing which color quadrant the robot started in.
   */
   
  //Serial.println("num set");
  while (!boundaryFound) {
    boundarySearch();
    forward();
    delay(100);
    stopMovement();
    delay(1000);
  }
  
  //displayLED(quadrant);
  delay(3000);
  stopMovement(); // Stop before second stage

  /*
   * Move only once to get into middle of quadrant
   * 
   */
   while (!hasMoved) {
    forward();
    delay(4000);
    stopMovement();
   }
  
  /* SECOND STATE OF PROGRAM*/
  /*
   * In this state, the PixyCam is used to check whether or not there 
   * are any egg blocks in view that are the same color as the 
   * color of the starting quadrant.
   */

  Serial.println("Calling eggSearch and printing out values");
  Serial.println();
  
  if (!eggFound) {
    eggSearch();
  }
  
  if (egg != initialNum) { // AKA Egg is FOUND
    stopMovement();
    printValues();
    delay(60000); // Stop for a minute 
  }

  /*
   * Turn if egg not found
   */
   leftTurn();

//  if (egg == initialNum && !(eggFound)) {
//    whiteLineTest();
//    
//    onGrayMat();
//    Serial.print("\n Times still on gray mat: ");
//    Serial.println(grayMatCounter);
//    if (grayMatCounter < 5) {
//        if (!whiteLineFound) {
//        Serial.println("Forward movement, 2 seconds");
//        forward();
//        delay(2000);
//        
//        Serial.println("Stop movement, 1 second");
//        stopMovement();
//        delay(1000);
//      }
//    }
//
//    if (grayMatCounter >= 4) {
//      if (!whiteLineFound) {
//      Serial.println("Forward movement, 2 seconds");
//      forward();
//      delay(500);
//      
//      Serial.println("Stop movement, 1 second");
//      stopMovement();
//      delay(1000);
//      }
//    }
//    
//    if (whiteLineFound) {
//      Serial.println("White Line Hit");
//      Serial.println("Backing Up");
//      reverse();
//      delay(4000);
//
//      Serial.println("Left Turn");
//      stopMovement();
//      delay(3000);
//      
//      Serial.println("Stopping");
//      stopMovement();
//      delay(10000);
//      whiteLineFound = 0;
//    }
    
  }
}
