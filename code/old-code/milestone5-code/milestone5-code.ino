/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 5
*************************************************************/

# include <Servo.h>
# include <SPI.h>
# include <Pixy.h>
# include <Adafruit_TCS34725.h>

// MISCELLANEOUS VARIABLES
int initialNum = -500;
int quadrant = 4;
int color = initialNum;
int caseNum = 1;

// MOTOR VARIABLES
int directionLeft = 13;
int directionRight = 12;
int brakeLeft = 8;
int brakeRight = 9;
int motorLeft = 11;
int motorRight = 3; 
int normalSpeed = 200;

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

// RGB SENSOR VARIABLES
Adafruit_TCS34725 tcs = Adafruit_TCS34725
    (TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t clear, sum, red, green, blue;
float r, g, b;

// IR SENSOR VARIABLES
int irLED = 53;

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

  //setting up rgb sensor
  tcs.begin();

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

  //setting up IR LED
  pinMode(irLED, INPUT);

}

void loop(){

  delay(1000);
  
  /*
  Serial.println("Boundary search using RGB sensor");
  boundarySearch();
   */
   
  Serial.println("Forward movement, 2 seconds");
  forward();
  delay(2000);

  Serial.print("Stop movement, 1 second");
  stopMovement();
  delay(1000);

  Serial.println("Calling eggSearch and printing out values");
  eggSearch();
  if (egg != initialNum) {
    printValues();
  }

  Serial.println("Forward movement, 2 seconds");
  forward();
  delay(2000);

  Serial.println("Stop movement, 1 second");
  stopMovement();
  delay(1000);

  Serial.println("Reverse movement, 2 seconds");
  reverse();
  delay(2000);

  Serial.println("Stop movement, 1 second");
  stopMovement();
  delay(1000);

  Serial.println("Left turn, then stop for 1 second");
  leftTurn();
  stopMovement();
  delay(1000);

  Serial.println("Right turn, then stop for 1 second");
  rightTurn();
  stopMovement();
  delay(1000);

  Serial.println("Spin, then stop for 1 second");
  spin();
  stopMovement();
  delay(1000);

  Serial.println("Slight right turn, then stop for 1 second");
  slightRightTurn();
  stopMovement();
  delay(1000);

  Serial.println("Slight left turn, then stop for 1 second");
  slightLeftTurn();
  stopMovement();
  delay(1000);

  
}

