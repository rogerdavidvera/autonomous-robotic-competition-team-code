/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 5 DEBUG VERSION
*************************************************************/

# include <Servo.h>
# include <SPI.h>
# include <Pixy.h>
# include <Adafruit_TCS34725.h>

Servo servoArm;
int arm = 40;

// MISCELLANEOUS VARIABLES
int initialNum = 500;
int quadrant = 0;
int color = initialNum;
int caseNum = 1;
int homebase = 0;

// MOTOR VARIABLES
int directionLeft = 13;
int directionRight = 12;
int brakeLeft = 8;
int brakeRight = 9;
int motorLeft = 11;
int motorRight = 3; 
int normalSpeed = 80;
int speed2 = 100; // Needed to overcome uneven/not straight movement

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

int hasMoved = 0;

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

  servoArm.attach(arm);

}

void loop() {

  /* FIRST STATE OF PROGRAM*/
  /*
   * In this state, if a boundary has not been found. The boundaryFound
   * variable is still equal to 0. So as long as condition that boundaryFound
   * is not ZERO, the while loop will keep continuing.
   * 
   * Once, a boundary is found. The quadrant variable is set to the number
   * describing which color quadrant the robot started in. The quadrant value
   * is then assigned to the variable homebase. Quadrant is then reset to 0
   * for later use.
   */

  leftTurn();
  slightRightTurn();
  forward();
  delay(1500);
  stopMovement();
  
  servoArm.write(175);
  while (!boundaryFound && homebase == 0) {
    boundarySearch();
    forward();
    delay(40);
    stopMovement();
    delay(40);
  }

  homebase = quadrant;
  quadrant = 0;
  
  //Move forward a bit more
  forward();
  delay(700);
  
  stopMovement(); // Stop before second stage


  if (egg == initialNum && !(eggFound)) {
    
    while (grayMatCounter < 2) { // While robot has not moved three times since boundary found
      onGrayMat();
      Serial.print("\n Times still on gray mat: ");
      Serial.println(grayMatCounter);
      
      Serial.println("\nForward movement, .5 seconds");
      forward();
      delay(500);
      
      Serial.println("Stop movement, .5 second");
      stopMovement();
      delay(500);
    }

    seeingGray(); // If robot is in grey, light all LEDS up
    spin(); // Spin around completely
    slightLeftTurn(); // Adjust a bit
    stopMovement();
    while (quadrant != homebase) { // While it has not detected homebase again
      boundarySearch();
      forward();
      delay(40);
      stopMovement();
      delay(40);
    } // Found homebase
    forward(); // Get into gray area
    delay(1500);
    stopMovement(); // Stop for 120 seconds,2 minutes
    delay(1200000);
  }
    
}
