/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 5 -- Functions for determining boundaries
*************************************************************/

// This method takes in RBG sensor input, 
// and determines the color based on 
// R, G, and B values. If it is not gray,
// it will set the quadrant color by calling
// displayLED

void boundarySearch() {

  tcs.setInterrupt(false);                    // turns on LED
  delay(60);
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);                     // turns off LED

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
        caseNum++;
        Serial.println("RBG SENSOR SEEING ORANGE");
      }

  else if ((int)r > 128 && (int)g >= 48 && (int)g <= 80 &&
           (int)b >= 43 && (int)b <= 83) {
        // color is Red
        quadrant = 1; 
        caseNum++;
        Serial.println("RBG SENSOR SEEING RED");
      }
      
   else if ((int)r >= 97 && (int)r <= 112 && (int)g >= 97 && 
            (int)g <= 148 && (int)b >= 41 && (int)b <= 60) {
        // color is Yellow
        quadrant = 3;
        caseNum++;
        Serial.println("RBG SENSOR SEEING YELLOW");
      }
      
   else if ((int)r >= 43 && (int)r <= 60 && (int)g >= 113 && 
            (int)g <= 127 && (int)b >= 65 && (int)b <= 79) {
        // color is Green
        quadrant = 4;
        caseNum++; 
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
  digitalWrite(redLED, LOW);
  digitalWrite(orangeLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  // display new LED
  switch(color) {
    case 1: 
      // CHANGE LED TO RED
      digitalWrite(redLED, HIGH);
      break;
    case 2:
      // CHANGE LED TO ORANGE
      digitalWrite(orangeLED, HIGH);
      break;
    case 3: 
      // CHANGE LED TO YELLOW
      digitalWrite(yellowLED, HIGH);
      break;
    case 4: 
      // CHANGE LED TO GREEN
      digitalWrite(greenLED, HIGH);
      break;
    case 5:
      break;
  }
}

