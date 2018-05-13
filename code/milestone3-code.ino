/*************************************************************
Team C Milestone 3
by Roger Vera, Tyler Kugler, Esther Xu
*************************************************************/

#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

static int i = 0;
int j;
uint16_t blocks;
char buf[32]; 
int ledColor = 5;
  
int ledRedPin = 2;
int ledOrangePin = 3;
int ledYellowPin = 4;
int ledGreenPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("starting");

  pixy.init();

  pinMode(ledRedPin, OUTPUT);
  pinMode(ledOrangePin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // get blocks from pixy
  blocks = pixy.getBlocks();

  if (blocks)
  {
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%50==0)
    {
      //sprintf(buf, "Detected %d:\n", blocks);
      //Serial.print(buf);
      for (j=0; j<blocks; j++) 
      {  
        //sprintf(buf, "  block %d: ", j);
        //Serial.println(buf); 
        pixy.blocks[j].print();
        
        int signature = pixy.blocks[j].signature;
        Serial.print("Signature of block: ");
        Serial.println(signature);
        
        int angle = pixy.blocks[j].angle;
        Serial.print("Angle of block: ");
        Serial.println(angle);

        determineClosest(signature, angle);
        displayLED(ledColor);
      }
    }
  }

}


// Uses the signature and angle information from pixy blocks
// to determine which color is closest to the robot
void determineClosest(int signature, int angle) {

   switch(signature) {
    case 11: // 13 Octal Red,Yellow
      if (angle >= 0) {
        ledColor = 1; // red
      } else {
        ledColor = 3; // yellow
      }
      break;
    case 12: // 14 Octal, Red,Green
      if (angle >= 0) {
        ledColor = 1; // red
      }
      else {
        ledColor = 4; // green
      }
      break;
    case 19: // 23 Octal, Orange,Yellow
      if (angle >= 0) {
        ledColor = 2; // orange
      }
      else {
        ledColor = 3; // yellow
      }
      break;
    case 20: //24 Octal Orange,Green
      if (angle >= 0) {
        ledColor = 2; // orange
      }
      else {
        ledColor = 4; // green
      }
      break;
    default:
      ledColor = 5;
      break;
   }
}

// displays the LED color given
// 1 = red, 2 = orange, 3 = yellow, 4 = green
void displayLED(int ledColor) {

  // Turn off all LEDs
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledOrangePin, LOW);
  digitalWrite(ledYellowPin, LOW);
  digitalWrite(ledGreenPin, LOW);

  // Print to Serial monitor
  Serial.println("%d is the closest color.");

  // display new LED
  switch(ledColor) {
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
      // print error message
      Serial.println("Error.");
  }
}
