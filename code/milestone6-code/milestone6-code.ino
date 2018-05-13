/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 6
*************************************************************/

# include <Servo.h>
# include <SPI.h>
# include <Pixy.h>
# include <Adafruit_TCS34725.h>

Servo servoArm;
int arm = 40;

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
int normalSpeed = 350; //120

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

  delay(1000);
  
  
   // Move left to find eggs that are in center of view

   servoArm.write(180);
   
   while (!eggFound) {
    Serial.println("Moving Left");
    slightLeftTurn();
    Serial.println("Calling EggSearch");
    eggSearch();
   }


  // Move forward with egg until out of boundaries
  
  if (eggFound) { // AKA Egg is FOUND
    Serial.println("Moving forward");
    servoArm.write(85);
    forward();
    delay(60000); // Stop for a minute 
    stopMovement();
  }

    
  }
