/*
   COMPETITION CODE
   OVIRAPTORS: Esther Xu, Roger Vera, Tyler Kugler
   MAP AND DISPLAY FUNCTIONS
*/

/*
   displayLED(int color) displays the LED color given
   1 = red, 2 = orange, 3 = yellow, 4 = green, 5 = gray/none
*/
void displayLED(int color) {

  // Turn off all LEDs
  digitalWrite(redLED, LOW);
  digitalWrite(orangeLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  // Display new LED color
  switch (color) {
    case 1:
      digitalWrite(redLED, HIGH);
      break;
    case 2:
      digitalWrite(orangeLED, HIGH);
      break;
    case 3:
      digitalWrite(yellowLED, HIGH);
      break;
    case 4:
      digitalWrite(greenLED, HIGH);
      break;
    case 5:
      break;
  }
}

void getAnalogAverage() {
  Serial.print(analogRead(leftDistanceIR));
  Serial.print("\t");
  Serial.print(analogRead(centerDistanceIR));
  Serial.print("\t");
  Serial.print(analogRead(rightDistanceIR));
  Serial.println("\t");
}

/*
   setLetters() will set the lettered quadrants to the correct color
   based on the home color
*/
void setLetters() {
  switch (homeColor) {
    case 1:
      quadA = 1;
      quadB = 3;
      quadC = 2;
      quadD = 4;
      break;
    case 2:
      quadA = 2;
      quadB = 4;
      quadC = 1;
      quadD = 3;
      break;
    case 3:
      quadA = 3;
      quadB = 2;
      quadC = 4;
      quadD = 1;
      break;
    case 4:
      quadA = 4;
      quadB = 1;
      quadC = 3;
      quadD = 2;
      break;
  }
}

/*
   getLetter(int color) will return the character associated with that
   color based on the mapping
*/
char getLetter(int color) {
  if (color == quadA) return 'A';
  else if (color == quadB) return 'B';
  else if (color == quadC) return 'C';
  else if (color == quadD) return 'D';
  else return 'G'; // for Gray
}

int getColor(char quadrant) {
  switch (homeColor) {
    case 1:
      switch (quadrant) {
        case 'A': return 1;
        case 'B': return 3;
        case 'C': return 2;
        case 'D': return 4;
      }
      break;
    case 2:
      switch (quadrant) {
        case 'A': return 2;
        case 'B': return 4;
        case 'C': return 1;
        case 'D': return 3;
      }
      break;
    case 3:
      switch (quadrant) {
        case 'A': return 3;
        case 'B': return 2;
        case 'C': return 4;
        case 'D': return 1;
      }
      break;
    case 4:
      switch (quadrant) {
        case 'A': return 4;
        case 'B': return 1;
        case 'C': return 3;
        case 'D': return 2;
      }
  }
}

/*
   printRGBValues will print out the current values read by an RGB sensor
*/
void printRGBValues(uint16_t r, uint16_t g, uint16_t b, uint16_t c, uint16_t lux) {
  Serial.print("Lux: "); Serial.print(lux); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r); Serial.print(" ");
  Serial.print("G: "); Serial.print(g); Serial.print(" ");
  Serial.print("B: "); Serial.print(b); Serial.print(" ");
  Serial.print("C: "); Serial.print(c); Serial.print(" ");
  Serial.println(" ");
}


/*
  Color to String will take in a number and print out it's correpsonding color
*/

String colorToString(int color) {
  switch (color) {
        case 1: return "RED";
        case 2: return "ORANGE";
        case 3: return "YELLOW";
        case 4: return "GREEN";
        default: return "ERROR";
  }
}

/*
 *  Esther: 
 *  To determine which direction to go if not going right into home
 */
 int homeDirection() {
  switch(lastQuadrant){
    case 'B': return 1; // 1 = go left
    case 'C': 
      switch(currentQuadrant){
        case 'D': return 1;
        case 'B': return 2;  // 2 = go right
      }
      break;
    case 'D': return 2;
  }
 }

