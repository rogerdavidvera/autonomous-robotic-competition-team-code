/*
   Milestone 9
   OVIRAPTORS: Esther Xu, Roger Vera, Tyler Kugler
*/

# include <Servo.h>
# include <SPI.h>
# include <Pixy.h>
# include <Adafruit_TCS34725softi2c.h>
# include <SoftwareWire.h>

// NOTE: BLACK TAG = SDA

/*
    VARIABLES DECLARED BELOW. SEPARATED BY CATEGORY
*/

// BOOLEANS
bool eggFound = false;                  // is an egg in view of the pixy?
bool eggInRange = false;                // is the egg in range of the pixy?
bool findStartingQ = true;              // is Ovi currently looking for its starting color?
bool findMyEggs = true;                 // is Ovi currently looking for eggs?
bool findHome = false;                  // is Ovi currently looking for its home quadrant
bool clearHomeQuadrant = true;          // does Ovi still need to clear its home quadrant?
bool whiteLine = false;

// MISCELLANEOUS 
int initialNumber = -50;
int eggsCollected = 0;                  // number of eggs collected
int tempColor = 5;
#define left 1
#define right 2
int whichSensor = 0;                    // which side should Ovi get sensor input from, left or right?

// BOUNDARIES
int currentColor;
char lastQuadrant = 'Z';
char currentQuadrant = 'Z';
int homeColor = 0;
int quadA, quadB, quadC, quadD;

// EGGS
int eggColor = 0;

// MOTORS
int directionLeft = 13;
int directionRight = 12;
int brakeLeft = 8;
int brakeRight = 9;
int motorLeft = 11;
int motorRight = 3;
double leftNormalSpeed = 120;
double rightNormalSpeed = 120;
double leftSpeed = leftNormalSpeed;
double rightSpeed = rightNormalSpeed;
int leftForward = 0;                    // Establishes the direction 
int leftBackward = 1;                   // of the wheels for forward 
int rightForward = 1;                   // and backward movement
int rightBackward = 0;

// SERVOS
Servo leftArm;
Servo rightArm;
Servo scoopServo;
Servo leftWallServo;
Servo rightWallServo;
Servo sortServo;
int leftArmPin = 39;
int rightArmPin = 38;
int scoopServoPin = 37;
int leftWallServoPin = 41;
int rightWallServoPin = 40;
int sortServoPin = 36;

      // LEDs
int redLED = 2;
int orangeLED = 4;
int yellowLED = 5;
int greenLED = 6;

      // RGB
#define sclPin 34
#define sdaPin 35
#define sclPinSort 42
#define sdaPinSort 43
#define ledPinRGBs 22

SoftwareWire myWire(35,34); // this might be unnecessary
Adafruit_TCS34725softi2c leftTCS = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X, 20, 21);
Adafruit_TCS34725softi2c rightTCS = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X, sdaPin, sclPin);
Adafruit_TCS34725softi2c sortTCS = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_4X, sdaPinSort, sclPinSort);
uint16_t clear, sum, red, green, blue;
float r, g, b;
int leftRGBLED = 22;
int rightRGBLED = 22; // whatever

// IR
int rightDistanceIR = A3;
int centerDistanceIR = A5;
int leftDistanceIR = A8;

// LINE-CHECKERS
int leftLineChecker = A14;
int rightLineChecker = A11;; // whatever

// PIXY
Pixy pixy;
static int i = 0;
uint16_t blocks;
char buf[32];
int x = initialNumber;                        // initialNumber is used
int y = initialNumber;                        // to determine whether
int width = initialNumber;                    // the pixy has actually
int height = initialNumber;                   // detected an egg or not
int egg = initialNumber;
int signature = initialNumber;
//int exactX = initialNumber;
int testY, testSignature;
float h, w, ratioHW;

void setup() {

  Serial.begin(9600);
  Serial.println("Starting...");

  /*
      These next lines will set up the pixy camera, RGB sensor, left and right
      motors, servo arms, LEDs, and IR sensors
  */

  pixy.init();
  Serial.println("Pixy set");

  leftTCS.begin();
  pinMode(leftRGBLED, OUTPUT);
  digitalWrite(ledPinRGBs, HIGH);

  rightTCS.begin();
  pinMode(rightRGBLED, OUTPUT);
  digitalWrite(ledPinRGBs, HIGH);

  sortTCS.begin();
  pinMode(ledPinRGBs, OUTPUT);
  digitalWrite(ledPinRGBs, HIGH);

  Serial.println("RGBs set");

  pinMode(directionLeft, OUTPUT);
  pinMode(brakeLeft, OUTPUT);
  pinMode(directionRight, OUTPUT);
  pinMode(brakeRight, OUTPUT);
  Serial.println("Left and right motors set");

  pinMode(redLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  Serial.println("LEDs set");

  leftArm.attach(leftArmPin);
  rightArm.attach(rightArmPin);
  scoopServo.attach(scoopServoPin);
  leftWallServo.attach(leftWallServoPin);
  rightWallServo.attach(rightWallServoPin);
  sortServo.attach(sortServoPin);
  Serial.println("Servo arms set");
  sortServo.write(110); // center value
  armsUp();
  pullWall();
  displayLED(1);
  delay(50);
  displayLED(2);
  delay(50);
  displayLED(3);
  delay(50);
  displayLED(4);
  delay(50);
  displayLED(5);
  Serial.println("All things set");
  spinFortyFive();
}

void loop() {
  /*
   * IS OVI AT A WHITE LINE?
   * lineCheck() uses a line checker on the left and right side to determine if Ovi
   *      at a line. This line is either white or a color boundary. If this returns true,
   *      we check the RGB sensors next for a more definitive answer. The line checker
   *      is used first instead of the more-accurate RGB sensor because the RGB sensor
   *      is computation-heavy and Ovi can't eggSearch properly if it gets run every loop
   * whiteLineTrigger() reads one of the RGB sensors based on the variable whichSensor. 
   *      This function returns true when the sensor reads the color under
   *      it as white, which means Ovi is at a white line.
   * escapeWhiteLine() will have Ovi reverse, spin, and then move forward, escaping the 
   *      white line. 
   * If whiteLineTrigger() returned false, Ovi moves forward for a short period of time
   *      to move out of the zone in which the line checker returned a false positive
   *      
   *      NOTE: Once we are implementing boundarySearch & eggSearch together, run the code
   *      with and without the stopMovement() line. Right now, it's commented out. I'm
   *      not sure if stopping every time the line checker returns positive is the best idea,
   *      considering it's finnicky and gives some false positives over the gray mat. However,
   *      there are two things to consider:
   *      (1) if Ovi doesn't stop, will Ovi occasionally go over the white line because he is
   *          moving while running whiteLineTrigger()?
   *      (2) if Ovi is finding eggs and we're moving while running whiteLineTrigger(), will
   *          he occasionally move and lose sight of an egg that would have been in vision had 
   *          he just stopped and then moved for 250ms after the computation?
   *      Having the stopMovement() in the code will cause Ovi to be semi-jittery. But if it makes
   *      him significantly more accurate, it's worth it.
   */
  leftSpeed = leftNormalSpeed;
  rightSpeed = rightNormalSpeed;
  
  if (rightRGBWhite() || leftRGBWhite()) {    // lineCheck() will return true if Ovi hits a color boundary or white line
      Serial.println("White Line Detected");
      escapeWhiteLine();
  }

  // timer function
  if (millis() >= 150000 && findMyEggs){
    findMyEggs = false;
    findHome = true;
  }
  /*
   * FIND STARTING QUADRANT
   * boundaryTrigger() will return true if Ovi is at any color boundary.
   * mapQuadrants() will call a boundarySearch which will set the homeColor and 
   *      set the map. See boundarySearch() in the sensorFunctions section for more information
   *      on the process.
   * If boundaryTrigger() returned false, just move in an arc to the left until a boundary is found.
   */
   
  if (findStartingQ) {              // this case is for finding the starting quadrant
    if (boundaryTrigger()) {        // boundaryTrigger() will return true is Ovi hits a color boundary
      mapQuadrants();               // if so, map the quadrants using a boundary search
      forward();
      delay(600);                   // We need that to fully exit the loop.
    }
    else {
      //arcLeft();                  // if not, arc left until a boundary is found
      forward();
    }
  }


 /*
  * FIND OVI'S EGGS
  * 
  * This code is currently commented out for proper testing of the other cases above. Once that
  * is settled, uncomment this code to test it together. I'll be reviewing this code in backwards order,
  * looking at the egg-searching process in the order that it would occur
  * 
  * eggSearch() will return true if Ovi sees an appropriate egg. If the inputs are (homeColor, true), 
  *       Ovi will search for an egg matching his homeColor. If the inputs are (homeColor, false), he'll
  *       search for all eggs that don't match his homeColor. Additionally, eggSearch() will set the boolean
  *       eggFound to true if an egg is found and to false otherwise. 
  * If eggSearch() returns false, immediately call it again to check. We found during testing that a second
  *       attempt increased our chances because it balanced out the computation-heavy white line checks. 
  *       Then, move in an arc to the left and try again in the next loop.
  * moveTowardEgg() is called when eggSearch() returns true. It uses the x coordinate of the egg Ovi found
  *       to set the left and right motor speeds, which is determined through a linear function.
  * isEggInRange() will call 3 IR sensors on the front of Ovi to determine if an egg is in range to be
  *       scooped up. If it is in range, it will return true and set the boolean eggInRange to true
  * if isEggInRange() and eggFound are both true, Ovi will do the following
  *       (1) stop moving
  *       (2) drop his arms down
  *       (3) push the wall forward, bringing the egg into range of the scoop
  *       (4) scoop the egg
  *       (5) lift his arms up, depositing the egg behind him
  *       (6) pull the wall back into its resting position
  *       (7) reverse, in the event that Ovi accidentally missed the egg
  *       Right now, Ovi automatically increments eggsCollected. If we can implement the sorting servo and
  *       sorting RGB, the eggsCollected will be incremented there.
  * I have removed the first case, which checked if an egg was in the scoop. Since we'd be scooping
  *       no matter what and the IR data wasn't especially reliable, I eliminated the case. 
  *       
  * At the end, we set findMyEggs to false and findHome to true so Ovi can return home.The number 3 was chosen
  * semi-randomly. It may be too ambitious to find all of the eggs, especially with Sufyan's team meddling.
  * I can explain my rationale in person, but honestly, all of the teams are doing shitty enough that scoring 3 
  * eggs would be enough for us to win. Sufyan's group is regularly scoring poorly; they succeed by making the other
  * teams' scores worse. If we get 3 eggs, we're basically untouchable. Based on their algorithm, their group tends to 
  * keep the number of eggs in each quadrant pretty stable. Thus, even if we have ~4 bad eggs in our arena, we still score
  * 5 points, which seems bad but is significantly better than the 2 points Sufyan's group gathered on Thursday. I think
  * at a certain point we could just agree to KISS -- keep it simple, stupid. Their group is likely to give us a bad
  * egg or two, so we shouldn't do it ourselves. 
  */

  else if (findMyEggs) {
    Serial.println("In FindMyEggs Stage");
    if (eggsCollected >= 4) {
      stopMovement();
      delay(200);
      findHome = true;
      findMyEggs = false;
    }
    if (eggFound && isEggInRange()) {
      stopMovement();
      reverse();
      delay(300);
      //displayLED(1); // was used during testing -- now obsolete
      repositionEgg();
      scoopEgg();
      sortEgg();
      //stopMovement();
      //delay(2000);
      reverse();
      delay(750);
      eggFound = false;
      eggInRange = false;
      //eggsCollected++;  // Obselete now, count included in EggSort
    }
    if (eggSearch(homeColor, true)) {
      moveTowardEgg();
    }
    else {
      //stopMovement();   // was used during testing -- now obsolete
      eggSearch(homeColor, true);
      //arcLeft();
      //forward();
      slightArcLeft();
      //displayLED(5);  // was used during testing -- now obsolete
    }
  }

  /*
   * FIND HOME
   * 
   * This code is currently commented out for proper testing of the other cases above. Once
   * our boundarySearch and whiteLine checks are working properly and efficiently, test this by 
   * doing the following:
   *    (1) set findStartingQ to false.
   *    (2) set homeColor = 1 in the setup. It can be any color, I just
   *        chose that one.
   *    (3) set currentQuadrant = 'D' or 'B'. 
   *    (4) set lastQuadrant = 'A'
   *    We do this because after our eggSearch, the currentQuadrant and lastQuadrant will likely
   *    be inaccurate, since they weren't set since before our eggSearch. It is fine,
   *    because these variables will be reset accurately once we run the first boundarySearch.
   *    (5) place Ovi anywhere in the arena
   *    
   * boundaryTrigger() will return true when Ovi is over a boundary.
   * If so, run boundarySearch() to set the current and last quadrants. 
   *    In this boundarySearch, if either quadrant is A, we will move
   *    into that quadrant and set findHome to false. 
   * Else, call goHome(), which uses the currentQuadrant and lastMovement
   *    to determine which way to move.
   * 
   */

 
  else if (findHome) {
    Serial.println("Finding Home");
    if (boundaryTrigger()) {
      boundarySearch();
    }
    else {
      goHome();
      Serial.println("Go Home");
    }
  }

  /*
   * Once we've returned home, we can entertain the thought of clearing out the quadrant,
   * but until we're able to do everything above, that's just wishful thinking. I will 
   * write that code when we get that far. Until now, it'll stop in the quadrant and 
   * do a victory dance (blinking the LEDs)!
   * 
   * It's commented out for now, just like the two above.
   */
  else {
    stopMovement();
    delay(2000000);  
  }
   /*
  else {
    stopMovement();
    displayLED(1);
    delay(50);
    displayLED(2);
    delay(50);
    displayLED(3);
    delay(50);
    displayLED(4);
    delay(50);
    displayLED(5);
    Serial.println("STOPPED -- DONE");
  } */
}
