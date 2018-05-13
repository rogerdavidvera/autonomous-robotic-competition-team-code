/*************************************************************
Team C Milestone 4
by Roger Vera, Tyler Kugler, Esther Xu
*************************************************************/

#include <Servo.h>
#include <SPI.h>
#include <Pixy.h>
#include <Adafruit_TCS34725.h>

Pixy pixy;
Servo servoLeft;
Servo servoRight;
int servoLeftPin = 9;
int servoRightPin = 10;
int signalLED = 53; 

static int i = 0;
int j;
uint16_t blocks;
char buf[32]; 

int ledRedPin = 2;
int ledOrangePin = 3;
int ledYellowPin = 4;
int ledGreenPin = 5;

int color = 5;
int caseNumber = 0;
int closestBlock = 500;
int correspondingEgg = 500;
int quadrant = 5;
int x = 500;
int y = 500;
int width = 0;
int height = 0;

uint16_t clear, sum, red, green, blue;
float r, g, b;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


void setup() {
  
  Serial.begin(9600);
  Serial.println("starting");

  pixy.init();
  tcs.begin();

  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);

  pinMode(ledRedPin, OUTPUT);
  pinMode(ledOrangePin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);

  pinMode(signalLED, INPUT);

}

void loop() {

  blocks = pixy.getBlocks();
  //whiteLineCheck();

  switch(caseNumber) {
    
    // Case 0: FIND THE BOUNDARY
    case 0:
      Serial.println("Case 0");
      forwardMovement();
      delay(500);
      stopMovement();
      boundarySearch();
      if (quadrant != 5) {
        caseNumber = 1;
        displayLED(quadrant);
      }
      break; 
      
    // Case 1: TURN AROUND FROM LOCATED BOUNDARY
    case 1: 
      Serial.println("Case 1");
      spin();
      stopMovement();
      delay(1000);
      caseNumber = 2;
      displayLED(5);
      
    // Case 2: SEARCH FOR CORRESPONDING EGG
    case 2: 
      Serial.println("Case 2");
      slightLeft(); 
      stopMovement();
      eggSearch(blocks);
      if (correspondingEgg != 500) {
        caseNumber++;
        break;
      }
      forwardMovement();
      delay(1000);
      stopMovement();
      eggSearch(blocks);
      if (correspondingEgg != 500) {
        caseNumber++;
      }
      break;
      
    // Case 3: FOUND AN EGG. TURN TOWARD IT
    case 3:
      Serial.println("Case 3");
      eggSearch(blocks);
        // egg lost, return to case 2
      if (correspondingEgg == 500) {
        caseNumber = 2;
        break;
      }
        // egg is centered, go to case 4
      else if (x >= 130 && x <= 190) {
        caseNumber = 4;
      }
        // egg is left of center, turn left 
      else if (x > 190) {
        slightLeft();
        break;
      }
        // egg is right of center, turn right
      else {
        slightRight();
        break;
      }
      
    // Case 4: EGG IS IN CENTER OF VIEW. MOVE TOWARD IT
    case 4:
      Serial.println("Case 4");
      eggSearch(blocks);
        // egg lost, go back to case 2
      if(x == 500 && y == 500) {
        caseNumber = 2;
        break;
      }
      else if ((width * height) >= 100) {
        caseNumber = 5;
        stopMovement();
      }
        // egg off center, go back to case 3
      else if (x < 120 || x > 200) {
        caseNumber = 3;
        break;
      }
        // else, move forward
      else {
        forwardMovement();
        delay(1000);
        stopMovement();
        break;
      }
      
    // Case 5: DONE. EGG FOUND. Blink LED.
    case 5:
      Serial.println("Case 5");
      displayLED(quadrant);
      delay(500);
      displayLED(5);
      delay(500);
}
}

void forwardMovement() {
  servoLeft.write(180);
  servoRight.write(79);
}

void stopMovement() {
  servoLeft.write(90);
  servoRight.write(90);
}

void reverseMovement() {
  servoLeft.write(0);
  servoRight.write(101);
}

void leftTurn() {
  servoLeft.write(0);
  servoRight.write(79);
  delay(2500);
}

void rightTurn() {
  servoLeft.write(180);
  servoRight.write(101);
  delay(2500);
}

void spin() {
  servoLeft.write(180);
  servoRight.write(101);
  delay(5000);
}

void slightLeft() {
  servoLeft.write(0);
  servoRight.write(79);
  delay(725);
}

void slightRight() {
  servoLeft.write(180);
  servoRight.write(101);
  delay(725);
}

void whiteLineCheck() {
  Serial.println("White line check");
  if (digitalRead(signalLED)) {
    Serial.print("White line detected, spinning around.");
    spin();
  }
}

// This method takes in RBG sensor input, 
// and determines the color based on 
// R, G, and B values. If it is not gray,
// it will set the quadrant color
void boundarySearch() {
  
  tcs.setInterrupt(false); // turns on LED
  delay(60);
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turns off LED

  sum = clear;
  r = red / sum;
  g = green / sum;
  b = blue / sum;
  r *= 256;
  g *= 256;
  b *= 256;

  if ((int)r >= 107 && (int)r <= 120 && (int)g >= 74 &&
      (int)g <= 80 && (int)b >= 73 && (int)b <= 83) {
        // color is Orange
        quadrant = 2;
        caseNumber++;
        Serial.println("RBG SENSOR SEEING ORANGE");
      }

  else if ((int)r > 128 && (int)g >= 48 && (int)g <= 80 &&
           (int)b >= 43 && (int)b <= 83) {
        // color is Red
        quadrant = 1; 
        caseNumber++;
        Serial.println("RBG SENSOR SEEING RED");
      }
      
   else if ((int)r >= 97 && (int)r <= 112 && (int)g >= 97 && 
            (int)g <= 148 && (int)b >= 41 && (int)b <= 60) {
        // color is Yellow
        quadrant = 3;
        caseNumber++;
        Serial.println("RBG SENSOR SEEING YELLOW");
      }
      
   else if ((int)r >= 43 && (int)r <= 60 && (int)g >= 113 && 
            (int)g <= 127 && (int)b >= 65 && (int)b <= 79) {
        // color is Green
        quadrant = 4;
        caseNumber++; 
        Serial.println("RBG SENSOR SEEING GREEN"); 
       }
       
   else if ((int)r >= 79 && (int)r <= 89 && (int)g >= 82 &&
            (int)g <= 90 && (int)b >= 68 && (int)b <= 74) {
       // color is Gray
       quadrant = 5;
       Serial.println("RBG SENSOR SEEING GRAY");
       }
       
   else {
     Serial.println("ERROR. OUT OF RANGES.");
     quadrant = 5;
   }
   displayLED(quadrant);
   
  
 
}


// displays the LED color given
// 1 = red, 2 = orange, 3 = yellow, 4 = green
void displayLED(int color) {

  // Turn off all LEDs
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledOrangePin, LOW);
  digitalWrite(ledYellowPin, LOW);
  digitalWrite(ledGreenPin, LOW);

  // display new LED
  switch(color) {
    case 1: 
      // CHANGE LED TO RED
      digitalWrite(ledRedPin, HIGH);
      break;
    case 2:
      // CHANGE LED TO ORANGE
      digitalWrite(ledOrangePin, HIGH);
      break;
    case 3: 
      // CHANGE LED TO YELLOW
      digitalWrite(ledYellowPin, HIGH);
      break;
    case 4: 
      // CHANGE LED TO GREEN
      digitalWrite(ledGreenPin, HIGH);
      break;
    case 5:
      break;
  }
}

// This method takes in blocks from the Pixy cam, 
// filters out any with color codes, and
// tries to find an egg
void eggSearch(uint16_t blocks) {
  
  correspondingEgg = 500;
  x = 500;
  y = 500; 
  width = 0;
  height = 0;
  
  if (blocks) {
    i++;
    if (i%50 == 0) {
      for (j=0; j < blocks; j++) {
        if (pixy.blocks[j].angle != 0) {
          continue;
        }
        // sig must equal quadrant and width-height ratio must be <= 2
        if (quadrant == pixy.blocks[j].signature && (pixy.blocks[j].width / pixy.blocks[j].height) <= 2) {
          // if there is no current egg, make j the stored egg
          if (correspondingEgg == 500) {
          correspondingEgg = j;
          }
          // if there is already a found egg, store the larger one
          else if (pixy.blocks[j].height > pixy.blocks[correspondingEgg].height
                  && pixy.blocks[j].width > pixy.blocks[correspondingEgg].width) {
            correspondingEgg = j;
          }
      }
      if (correspondingEgg == 500) {
        Serial.println("No block found. Re-entering case 2 pr 3.");
      }
      else {
        Serial.println("Corresponding block found!.");
        x = pixy.blocks[j].x;
        y = pixy.blocks[j].y;
        width = pixy.blocks[j].width;
        height = pixy.blocks[j].height;
      } 
    }
  }
}
}

