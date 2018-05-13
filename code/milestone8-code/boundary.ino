/*
   COMPETITION CODE
   OVIRAPTORS: Esther Xu, Roger Vera, Tyler Kugler
   BOUNDARY FUNCTIONS

   DETECTING WHITE LINES
      whiteLineTrigger() -- returns true if the RGB on the side in question
          is over a white boundary
      leftWhiteCheck() -- checks the left RGB for white
      rightWhiteCheck() -- checks the right RGB for white

      
   DETECTING BOUNDARIES
      boundaryTrigger() -- returns true if either RGB is over a color boundary
          also sets whichSensor to isolate the incident to one side
      leftColorCheck() -- checks the left RGB for any color
      rightColorCheck() -- checks the right RGB for any color
      mapQuadrants() -- calls boundarySearch(), ensures that the map is set
      boundarySearch() -- sets currentQuadrant and lastQuadrant based on RGB
          readings gathered from the side in question from boundaryTrigger()
      leftBoundaryFind() -- sets currentColor using the left RGB
      rightBoundaryFind() -- sets currentColor using the right RGB
*/

/*
   whiteLineTrigger() will return true if Ovi is at a white line and
   false otherwise. This is determined by an RGB sensor. It will run
   the test ten times, alternatively checking the left and right RGB
   sensor.
*/
bool whiteLineTrigger() {
  uint16_t r, g, b, c, lux;
  for (int i = 0; i < 10; i++) {
    if (whichSensor == left) {
      //delay(20);
      leftTCS.getRawData(&r, &g, &b, &c);
      lux = leftTCS.calculateLux(r, g, b);
      printRGBValues(r, g, b, c, lux);
      if (leftWhiteCheck(r, g, b, lux)) {          // this will return true if the left TCS reads white
        Serial.println("THE LEFT RGB SENSOR HAS DETECTED A WHITE LINE.");
        return true;
      }
    }
    else {
      //delay(20);
      rightTCS.getRawData(&r, &g, &b, &c);
      lux = rightTCS.calculateLux(r, g, b);
      printRGBValues(r, g, b, c, lux);
      if (rightWhiteCheck(r, g, b, lux)) {
        Serial.println("THE RIGHT RGB SENSOR HAS DETECTED A WHITE LINE.");
        return true;
      }
    }
  }
  Serial.println("NO WHITE LINE HAS BEEN DETECTED.");
  return false;
}

/*
   leftWhiteCheck() will return true iff the color is white under the left RGB
*/
bool leftWhiteCheck(uint16_t red, uint16_t green, uint16_t blue, uint16_t l) {
  if ((l >= 78 && l <= 170 &&
       red >= 100 && red <= 235 &&
       green >= 100 && green <= 265 &&
       blue >= 100 && blue <= 230) ||
      (l >= 310 && l <= 470 &&  // Mild raised edge in corners
       red >= 550 && red <= 570 &&
       green >= 650 && green <= 680 &&
       blue >= 550 && blue <= 580) ||
      (l >= 200 && l <= 260 &&  // Severe raised edge in corners
       red >= 265 && red <= 335 &&
       green >= 304 && green <= 330 &&
       blue >= 250 && blue <= 330) ||
      (l >= 202 && l <= 300 &&  // Corner White of Yellow
       red >= 270 && red <= 335 &&
       green >= 310 && green <= 330 &&
       blue >= 270 && blue <= 330)) {
    return true;
  }
  return false;
}

/*
   rightWhiteCheck() will return true iff the color is white under the right RGB
*/
bool rightWhiteCheck(uint16_t red, uint16_t green, uint16_t blue, uint16_t l) {
  if ((l >= 85 && l <= 170 &&
       red >= 100 && red <= 235 &&
       green >= 100 && green <= 265 &&
       blue >= 100 && blue <= 230) ||
      (l >= 310 && l <= 470 &&  // Mild raised edge in corners
       red >= 550 && red <= 570 &&
       green >= 650 && green <= 680 &&
       blue >= 550 && blue <= 580) ||
      (l >= 218 && l <= 300 &&  // Severe raised edge in corners
       red >= 270 && red <= 335 &&
       green >= 310 && green <= 360 &&
       blue >= 270 && blue <= 330) ||
       (l >= 284 && l <= 309 &&  // Corner White of Yellow
       red >= 388 && red <= 415 &&
       green >= 446 && green <= 480 &&
       blue >= 402 && blue <= 430)) {
    return true;
  }
  return false;
}


/*
    boundaryTrigger() will return true if one of the RGB sensors is over a color boundary.
    This function calls a helper function, colorCheck.
    This function will also save which sensor found a color in the variable, whichSensor
    whichSensor = 1 means LEFT, whichSensor = 2 means RIGHT
*/
bool boundaryTrigger() {
  uint16_t r, g, b, c, lux;

  // RUN TEN ATTEMPTS -- THIS IS A REDUNDANCY, BUT IF A COLOR IS DETECTED EARLY, IT WILL BREAK OUT VIA A RETURN CALL
  for (int i = 0; i < 10; i++) {

    //delay(20);
    leftTCS.getRawData(&r, &g, &b, &c);
    lux = leftTCS.calculateLux(r, g, b);
    printRGBValues(r, g, b, c, lux);
    Serial.println("Left RGB Values in boundaryTrigger()");
    if (leftWhiteCheck(r, g, b, lux)){
      Serial.println("THE LEFT RGB SENSOR HAS DETECTED A WHITE LINE.");
      escapeWhiteLine();
      return false;
    }
    else if (leftColorCheck(r, g, b, lux)) {                       // this will return true if the left TCS reads a color
      Serial.println("THE LEFT RGB SENSOR HAS DETECTED A COLOR BOUNDARY.");
      whichSensor = left;
      return true;
    }
    rightTCS.getRawData(&r, &g, &b, &c);
    lux = rightTCS.calculateLux(r, g, b);
    printRGBValues(r, g, b, c, lux);
    Serial.println("Right RGB Values in boundaryTrigger()");
    if (rightWhiteCheck(r, g, b, lux)){
      Serial.println("THE RIGHT RGB SENSOR HAS DETECTED A WHITE LINE.");
      escapeWhiteLine();
      return false;
    }
  }

  // END OF FOR-LOOP
  Serial.println("NO COLOR BOUNDARY HAS BEEN DETECTED.");
  return false;
}

/*
   leftColorCheck() will return true iff a color is detected under the left RGB
   This function does NOT return or save which color is found. This is because the function
   that calls this, boundaryTrigger(), is not precise enough -- there is a high likelihood 
   that the color Ovi finds is not the lastQuadrant color. This just starts the boundarySearch
   process
*/
bool leftColorCheck(uint16_t red, uint16_t green, uint16_t blue, uint16_t l) {
  if (l >= 65000 && blue < 70) {
    Serial.println("The Left RGB has seen RED -- colorCheck() method");
    return true;
  }
  else if (l >= 75 &&
           l <= 235 && //350
           red >= 99 &&
           red <= 316 &&
           green >= 90 &&
           green <= 250 &&
           blue >= 37 &&
           blue <= 102) {
    Serial.println("The Left RGB has seen YELLOW -- colorCheck() method1");
    return true;
  }
  else if (l >= 44 &&
           l <= 145 &&
           green >= 45 &&
           red <= 55 &&
           blue > 25 &&
           blue < 82) {
    Serial.println("The Left RGB has seen GREEN -- colorCheck() method");
    return true;
  }
  else if (l >= 12 &&
           l <= 60 &&
           red >= 84 &&
           red <= 225 &&
           green >= 45 &&
           green <= 155 &&
           blue >= 30) {
    Serial.println("The Left RGB has seen ORANGE -- colorCheck() method");
    return true;
  }
  else {
    Serial.println("The Left RGB has seen an UNKNOWN, GREY, or WHITE color -- colorCheck() method");
    return false;
  }
}

/*
   rightColorCheck() will return true iff a color is detected under the right RGB
   This function does NOT return or save which color is found. This is because the function
   that calls this, boundaryTrigger(), is not precise enough -- there is a high likelihood 
   that the color Ovi finds is not the lastQuadrant color. This just starts the boundarySearch
   process
*/
bool rightColorCheck(uint16_t red, uint16_t green, uint16_t blue, uint16_t l) {
  if (l >= 65000 && blue < 60) {
    Serial.println("The Right RGB has seen RED -- colorCheck() method");
    return true;
  }
  else if (l >= 82 &&
           l <= 160 &&
           red >= 108 &&
           red <= 316 &&
           green >= 96 &&
           green <= 310 &&
           blue >= 40 &&
           blue <= 90) {
    Serial.println("The Right RGB has seen YELLOW -- colorCheck() method");
    return true;
  }
  else if (l >= 35 && //41
           l <= 145 &&
           green >= 40 &&
           red <= 55 &&
           blue > 24 &&
           blue < 82) {
    Serial.println("The Right RGB has seen GREEN -- colorCheck() method");
    return true;
  }
  else if (l >= 12 &&
           l <= 60 &&
           red >= 108 &&
           red <= 225 &&
           green >= 50 &&
           green <= 155 &&
           blue >= 39) { //65?
    Serial.println("The Right RGB has seen ORANGE -- colorCheck() method");
    return true;
  }
  else {
    Serial.println("The Right RGB has seen an UNKNOWN, GREY, or WHITE color -- colorCheck() method");
    return false;
  }
}

/*
   mapQuadrants() will run a boundary search in order to determine the home quadrant as well
   as the new quadrant is has entered. Using the lastQuadrant and currentQuadrant, this function
   will set the map
*/
void mapQuadrants() {
  whichSensor = left;               // right now, I decide that whichSensor should be set to left
                                    // because we know it is reliable. If the right side is as reliable,
                                    // we can comment this out entirely, since whichSensor is set inside
                                    // rightColorCheck() / leftColorCheck()
  boundarySearch();                 // setting the map happens inside boundarySearch()
  Serial.println("Returned from boundarySearch() in mapQuadrants()");
  Serial.print("Current Q:"); Serial.println(currentQuadrant);
  Serial.print("Last Q:"); Serial.println(lastQuadrant);

  if (currentQuadrant != 'Z' && lastQuadrant != 'Z') {
    Serial.print("The map has been set. Our home color is ");
    //Serial.print(homeColor);
    Serial.print(colorToString(homeColor));
    Serial.print(" and the color of the current quadrant is ");
    //Serial.println(getColor(currentQuadrant));
    Serial.print(colorToString(getColor(currentQuadrant)));
    findStartingQ = false;
    Serial.println("findStartingQ is set to false");

  }

  else {
    Serial.println("Ovi failed to map the quadrants. Reversing so that another attempt can be made");
    reverse();
    delay(3000);
    stopMovement();
  }
}

/*
   boundarySearch() uses a ballistic approach to determine the lastQuadrant and the currentQuadrant
   Depending on which side (whichSensor == left vs whichSensor == right), it will call either
   leftBoundaryFind or rightBoundaryFind. These functions set currentColor, which we use to set
   tempLastQuadrant and tempCurrentQuadrant. If everything goes smoothly, these get set to the actual
   lastQuadrant and currentQuadrant variables. One key difference: the temporary values hold ints, but 
   the actual variables hold characters. 

   Here's what Ovi will do in this function:
      (1) reverse for 750ms
      (2) enter the proper whichSensor branch
      (3) stepForward() until the respective boundaryFind() sets currentColor to an actual color.
          This is the color of the quadrant we are leaving, or tempLastQuadrant
      (4) reset currentColor to 0
      (5) move forward for 500ms. This is done to skip over the point where the two strips of tape meet,
          which is notorious for giving false positives for orange and yellow
      (6) from there, stepBackward() until the respective boundaryFind() sets currentColor to an 
          an actual color. This is the color of the quadrant we have entered, or tempCurrentQuadrant
      (7) if currentColor is equal to tempLastQuadrant, Ovi has screwed up and missed either the old
          boundary or the new boundary. To rectify this, we just call boundarySearch again 
      (8) otherwise, set homeColor, if necessary
      (9) set currentQuadrant and lastQuadrant
      (10) if Ovi is trying to find home and the current quadrant is A, move forward and set findHome
          to false, since Ovi is home. Move forward a bit to ensure all of Ovi is in the quadrant. If 
          Ovi is trying to find home and the last quadrant is A, set findHome to false, and then spin
          and move forward for a slightly longer period of time to ensure all of Ovi is in the quadrant
      (11) move forward for 500 ms to get away from the boundary

          I've put the numbering in below
*/
void boundarySearch() {
  currentColor = 0;
  int tempLastQuadrant = 0;
  int tempCurrentQuadrant = 0;

  // (1)
  reverse();
  delay(750);
  stopMovement();

  uint16_t r, g, b, c, colorTemp, lux;

  // (2)
  if (whichSensor == left) { 
    // (3)
    while (currentColor == 0 && tempLastQuadrant == 0) {
      whiteLine = false;
      stepForward();
      leftBoundaryFind();
      if (whiteLine){
        escapeWhiteLine();
        whiteLine = false;
        return;
      }
    }
    tempLastQuadrant = currentColor;
    Serial.print("tempLastQuadrant has been set to ");
    Serial.println(colorToString(tempLastQuadrant));
    displayLED(tempLastQuadrant);
    if (currentColor == homeColor) {
      findHome = false;
      forward();
      delay(5000);
      return;
    }
    // (4)
    currentColor = 0;

    // (5)
    forward();
    delay(700);

    // (6)
    while (currentColor == 0 && tempCurrentQuadrant == 0) {
      whiteLine = false;
      stepBackward();
      leftBoundaryFind();
      if (whiteLine){
        escapeWhiteLine();
        whiteLine = false;
        return;
      }
      // (7)
      if (currentColor == tempLastQuadrant) { // an error has occurred
        Serial.println("Current color == last color; try again");
        displayLED(5);
        boundarySearch();
      }
    }
    tempCurrentQuadrant = currentColor;
    displayLED(tempCurrentQuadrant);
    currentColor = 0;
    Serial.print("tempCurrentQuadrant has been set to ");
    Serial.println(colorToString(tempLastQuadrant));

    // (8)
    if (homeColor == 0) {
      homeColor = tempLastQuadrant;
      Serial.print("homeColor has been set to ");
      Serial.println(colorToString(homeColor));
      setLetters();
    }

    // (9)
    currentQuadrant = getLetter(tempCurrentQuadrant);
    lastQuadrant = getLetter(tempLastQuadrant);
    Serial.print("currentQuadrant and lastQuadrant have been set to ");
    Serial.print(currentQuadrant); Serial.print(" and ");
    Serial.println(lastQuadrant);
    displayLED(5);

    // (10)
    if (findHome && lastQuadrant == 'A') {
      spin();
      findHome = false;
      forward();
      delay(3000);
      Serial.println("Home was found, backwards :)\n\n");
      stopMovement();
      delay(30000000000);
    }
    
    else if (findHome && currentQuadrant == 'A') {
      findHome = false;   
      Serial.println("Home was found :)\n\n");
      forward();
      delay(3000);
      stopMovement();
      delay(30000000000);
    }


   

/* 
 *  if crossing BC or CD, arc left to get home
 *  if crossing CB or DC, arc right to get home
 */
    else if (findHome && currentQuadrant != 'A' && lastQuadrant != 'A'){
      if (homeDirection() == 1){
        Serial.println("Going Left");
        //arcLeft();
        //delay(200);
      }
      else if (homeDirection() == 2){
        Serial.println("Going Right");
        //arcRight();
        //delay(200);
      }
      else {
        Serial.println("Going Straight");
        //forward();
        //delay(200);
      }
    }

     // (11)
    forward();
    delay(600);
  }


  // (2)
  if (whichSensor == right) {

    // (3)
    while (currentColor == 0 && tempLastQuadrant == 0) {
      whiteLine = false;
      stepForward();
      rightBoundaryFind();
      if (whiteLine){
        escapeWhiteLine();
        whiteLine = false;
        return;
      }
    }
    tempLastQuadrant = currentColor;
    Serial.print("tempLastQuadrant has been set to ");
    Serial.println(colorToString(tempLastQuadrant));
    displayLED(tempLastQuadrant);

    // (4)
    currentColor = 0;

    // (5)
    forward();
    delay(700);

    // (6)
    while (currentColor == 0 && tempCurrentQuadrant == 0) {
      whiteLine = false;
      stepBackward();
      rightBoundaryFind();
      if (whiteLine){
        escapeWhiteLine();
        whiteLine = false;
        return;
      }

      // (7)
      if (currentColor == tempLastQuadrant) { // an error has occurred
        Serial.println("Current color == last color; try again");
        displayLED(5);
        boundarySearch();
      }
    }
    tempCurrentQuadrant = currentColor;
    displayLED(tempCurrentQuadrant);
    currentColor = 0;
    Serial.print("tempCurrentQuadrant has been set to ");
    Serial.println(colorToString(tempLastQuadrant));

    // (8)
    if (homeColor == 0) {
      homeColor = tempLastQuadrant;
      Serial.println("homeColor has been set to ");
      Serial.println(colorToString(homeColor));
      setLetters();
    }

    // (9)
    currentQuadrant = getLetter(tempCurrentQuadrant);
    lastQuadrant = getLetter(tempLastQuadrant);
    Serial.print("currentQuadrant and lastQuadrant have been set to ");
    Serial.print(colorToString(currentQuadrant)); Serial.print(" and ");
    Serial.println(colorToString(lastQuadrant));
    displayLED(5);
    // (10)
    if (findHome && lastQuadrant == 'A') {
      spin();
      findHome = false;
      forward();
      delay(3000);
      Serial.println("Home was found, backwards :)\n\n");
    }
    
    else if (findHome && currentQuadrant == 'A') {
      findHome = false;   
      Serial.println("Home was found :)\n\n");
      forward();
      delay(3000);
    }

/* 
 *  if crossing BC or CD, arc left to get home
 *  if crossing CB or DC, arc right to get home
 */
    else if (findHome && currentQuadrant != 'A' && lastQuadrant != 'A'){
      if (homeDirection() == 1){
        Serial.println("Going Left");
        //arcLeft();
        //delay(200);
      }
      else if (homeDirection() == 2){
        Serial.println("Going Right");
        //arcRight();
        //delay(200);
      }
      else {
        Serial.println("Going Straight");
        //forward();
        //delay(200);
      }
    }
    
    // (11)
    forward();
    delay(600);
  }
}

/*
   leftBoundaryFind() will use the left RGB sensor to set currentColor
*/
void leftBoundaryFind() {

  /// consider doing up to five attempts???
  uint16_t r, g, b, c, l;
  //delay(20);
  leftTCS.getRawData(&r, &g, &b, &c);
  l = leftTCS.calculateLux(r, g, b);
  printRGBValues(r, g, b, c, l);
  if (leftWhiteCheck(r,g,b,l)){
    whiteLine = true;
    return;
  }
  else if (l >= 65000 && b < 60) {
    Serial.println("The Left RGB has seen RED -- colorCheck() method");
    currentColor = 1;
  }
  else if (l >= 75 &&
           l <= 235 && //350
           r >= 99 &&
           r <= 316 &&
           g >= 90 &&
           g <= 250 &&
           b >= 37 &&
           b <= 102) {
    Serial.println("The Left RGB has seen YELLOW -- colorCheck() method 2");
    currentColor = 3;
  }
  else if (l >= 44 &&
           l <= 145 &&
           g >= 42 &&
           r <= 45 &&
           b > 25 &&
           b < 82) {
    Serial.println("The Left RGB has seen GREEN -- colorCheck() method");
    currentColor = 4;
  }
  else if (l >= 12 &&
           l <= 60 && 
           r >= 84 && //v1: 95
           r <= 225 &&
           g >= 45 && //v1: 50
           g <= 155 &&
           b >= 30) { // v1: 34
    Serial.println("The Left RGB has seen ORANGE -- colorCheck() method");
    currentColor = 2;
  }
  else {
    Serial.println("The Left RGB has seen an UNKNOWN, GREY, or WHITE color -- colorCheck() method 2\n\n");
    printRGBValues(r, g, b, c, l);
  }
}

/*
   rightBoundaryFind() will use the right RGB sensor to set currentColor
*/
void rightBoundaryFind() {
  /// consider doing up to five attempts???
  uint16_t r, g, b, c, l;
  //delay(20);
  rightTCS.getRawData(&r, &g, &b, &c);
  l = rightTCS.calculateLux(r, g, b);
  printRGBValues(r, g, b, c, l);
  if (rightWhiteCheck(r,g,b,l)){
    Serial.println("White Line");
    whiteLine = true;
    return;
  }
  else if (l >= 65000 && b < 60) {
    Serial.println("The Left RGB has seen RED -- colorCheck() method");
    currentColor = 1;
  }
  else if (l >= 82 &&
           l <= 160 &&
           r >= 108 &&
           r <= 316 &&
           g >= 96 &&
           g <= 310 &&
           b >= 40 &&
           b <= 90) {
    Serial.println("The Left RGB has seen YELLOW -- colorCheck() method");
    currentColor = 3;
  }
  else if (l >= 35 && //41
           l <= 145 &&
           g >= 40 &&
           r <= 55 &&
           b > 24 &&
           b < 82) {
    Serial.println("The Left RGB has seen GREEN -- colorCheck() method");
    currentColor = 4;
  }
  else if (l >= 12 &&
           l <= 60 &&
           r >= 108 &&
           r <= 225 &&
           g >= 50 &&
           g <= 155 &&
           b >= 39) { //65?
    Serial.println("The Left RGB has seen ORANGE -- colorCheck() method");
    currentColor = 2;
  }
  else {
    Serial.println("The Left RGB has seen an UNKNOWN, GREY, or WHITE color -- colorCheck() method");
    //return false;
  }
}



////////

bool rightRGBWhite() {
  // consider doing up to five attempts???
  uint16_t r, g, b, c, l;
  rightTCS.getRawData(&r, &g, &b, &c);
  l = rightTCS.calculateLux(r, g, b);
  return rightWhiteCheck(r,g,b,l);
}

bool leftRGBWhite() {
  // consider doing up to five attempts???
  uint16_t r, g, b, c, l;
  leftTCS.getRawData(&r, &g, &b, &c);
  l = leftTCS.calculateLux(r, g, b);
  return leftWhiteCheck(r,g,b,l);
}
