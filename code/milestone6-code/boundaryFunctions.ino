
/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 5 -- Functions for determining boundaries
*************************************************************/

// This method takes in RBG sensor input, 
// and determines the color based on 
// R, G, and B values. If it is not gray,
// it will set the quadrant color by calling
// displayLED

int boundarySearch() {

// good
  tcs.setInterrupt(false);                    // turns on LED
  delay(60); //50ms to read
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);                     // turns off LED

//  good
  uint32_t sum = clear;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256;
  g *= 256;
  b *= 256;

  if ((int)r >= 110 && (int)r <= 132 && (int)g >= 68 &&
      (int)g <= 78 && (int)b >= 45 && (int)b <= 56) {
        // color is Orange
        quadrant = 2;
        caseNum++;
        Serial.println("RBG SENSOR SEEING ORANGE");
        boundaryFound = 1;
      }

  else if ((int)r > 136 && (int)g >= 46 && (int)g <= 63 &&
           (int)b >= 45 && (int)b <= 51) {
        // color is Red
        quadrant = 1; 
        caseNum++;
        Serial.println("RBG SENSOR SEEING RED");
        boundaryFound = 1;
      }
      
   else if ((int)r >= 101 && (int)r <= 109 && (int)g >= 93 && 
            (int)g <= 100 && (int)b >= 37 && (int)b <= 46) {
        // color is Yellow
        quadrant = 3;
        caseNum++;
        Serial.println("RBG SENSOR SEEING YELLOW");
        boundaryFound = 1;
      }
      
   else if ((int)r >= 58 && (int)r <= 77 && (int)g >= 104 && 
            (int)g <= 115 && (int)b >= 62 && (int)b <= 67) {
        // color is Green
        quadrant = 4;
        caseNum++; 
        Serial.println("RBG SENSOR SEEING GREEN");
        boundaryFound = 1; 
       }
       
   else if ((int)r >= 82 && (int)r <= 94 && (int)g >= 84 &&
            (int)g <= 87 && (int)b >= 68 && (int)b <= 74) {
       // color is Gray
       quadrant = 5;
       Serial.println("RBG SENSOR SEEING GRAY");
       }
       
   else {
       Serial.println("ERROR. OUT OF RANGES.");
       quadrant = 5;
   }
   Serial.print("Boundary found?: ");  
   Serial.println(boundaryFound);
   Serial.print("Started in quadrant: ");  
   switch(quadrant) {
    case 1:
      Serial.println("Red");
      break;
    case 2:
      Serial.println("Orange");
      break;
    case 3:
      Serial.println("Yellow");
      break;
    case 4:
      Serial.println("Green");
      break;
    default:
      Serial.println("Unknown");    
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
      delay(1000);
      digitalWrite(redLED, LOW);
      break;
    case 2:
      // CHANGE LED TO ORANGE
      digitalWrite(orangeLED, HIGH);
      delay(1000);
      digitalWrite(orangeLED, LOW);
      break;
    case 3: 
      // CHANGE LED TO YELLOW
      digitalWrite(yellowLED, HIGH);
      delay(1000);
      digitalWrite(yellowLED, LOW);
      break;
    case 4: 
      // CHANGE LED TO GREEN
      digitalWrite(greenLED, HIGH);
      delay(1000);
      digitalWrite(greenLED, LOW);
      break;
    case 5:
      break;
  }
}

void blinkLED(int color) {

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
      delay(500);
      digitalWrite(redLED, LOW);
      delay(500);
      break;
    case 2:
      // CHANGE LED TO ORANGE
      digitalWrite(orangeLED, HIGH);
      delay(500);
      digitalWrite(orangeLED, LOW);
      delay(500);
      break;
    case 3: 
      // CHANGE LED TO YELLOW
      digitalWrite(yellowLED, HIGH);
      delay(500);
      digitalWrite(yellowLED, LOW);
      delay(500);
      break;
    case 4: 
      // CHANGE LED TO GREEN
      digitalWrite(greenLED, HIGH);
      delay(500);
      digitalWrite(greenLED, LOW);
      delay(500);
      break;
    case 5:
      break;
  }

}

void whiteLineTest() {
  // good
  tcs.setInterrupt(false);                    // turns on LED
  delay(60); //50ms to read
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);                     // turns off LED

  //  good
  uint32_t sum = clear;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256;
  g *= 256;
  b *= 256;

//  Serial.print("\t");
//  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
//  Serial.println();
  if ((int)r >= 78 && (int)r <= 79 && (int)g == 87 && (int)b == 75) {
    // color is Orange
    quadrant = 2;
    caseNum++;
    Serial.println("WHITE LINE DETECTED");
    whiteLineFound = 1;
  } else {
    whiteLineFound = 0;
  }
}

void onGrayMat() {
  // good
  tcs.setInterrupt(false);                    // turns on LED
  delay(60); //50ms to read
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);                     // turns off LED

  //  good
  uint32_t sum = clear;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256;
  g *= 256;
  b *= 256;
  
  if ((int)r >= 82 && (int)r <= 94 && (int)g >= 84 &&
      (int)g <= 87 && (int)b >= 68 && (int)b <= 74) {
    // color is Gray
    Serial.println("ROBOT STILL IN GRAY MAT");
    grayMatCounter++;
  }
}
