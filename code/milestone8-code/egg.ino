/* 
 * COMPETITION CODE
 * OVIRAPTORS: Esther Xu, Roger Vera, Tyler Kugler
 * EGG FUNCTIONS (PIXY & IR)
 */

/*
 * eggSearch() takes two inputs: the home color and whether 
 * the pixy cam should look for eggs that match that color 
 * or eggs that don't match that color. it uses the pixy cam
 * to determine whether an egg that matches those qualifications
 * is in the view of Ovi
 */
bool eggSearch(int homeColor, bool match) {

    Serial.println("Calling getBlocks");
    delay(50);
    blocks = pixy.getBlocks();
   // blocks = pixy.getBlocks();
    Serial.print("Number of blocks returned: ");
    Serial.println(blocks);
    Serial.println();


    // built-in redundancy
    int attempts = 0;
    while (attempts < 5 && !blocks) {
      Serial.print("Calling getBlocks, attempt number ");
      Serial.println(attempts);
      Serial.print("Number of blocks returned: ");
      Serial.println(blocks);
      blocks = pixy.getBlocks();
      attempts++;
      }
    resetBlocks();
    if (blocks) {
      for (int j = 0; j < blocks; j++) {
        testY = pixy.blocks[j].y;
        testSignature = pixy.blocks[j].signature;
        ratioHW = pixy.blocks[j].height / pixy.blocks[j].width;

        // if we're looking for matches to our home color, make sure signature == homeColor
        // if we're looking for non-matches, make sure signature != homeColor
        // make sure the ratio is ~1 to rule out the tape showing as an egg
        if (((match && (testSignature == homeColor)) || (!match && (testSignature != homeColor)))
            && ((ratioHW > 0.90) || testY < 160)) {

              // if there is no current egg, make egg = j
              if (egg == initialNumber) {
                egg = j;
                x = pixy.blocks[j].x;
                y = pixy.blocks[j].y;
                width = pixy.blocks[j].width;
                height = pixy.blocks[j].height;
                signature = pixy.blocks[j].signature;
              }

              // else, see which egg is closer and use that one
              else if ((pixy.blocks[j].width > pixy.blocks[egg].width) &&
                       (pixy.blocks[j].height > pixy.blocks[egg].height)) {
                egg = j;
                x = pixy.blocks[j].x;
                y = pixy.blocks[j].y;
                width = pixy.blocks[j].width;
                height = pixy.blocks[j].height;
                signature = pixy.blocks[j].signature; 
              }
            }
      }}

      if (egg == initialNumber) {
        displayLED(5);
        Serial.println("No egg found");
        eggFound = false;
        leftSpeed = leftNormalSpeed;
        rightSpeed = rightNormalSpeed;
        return false;
      }
      else {
        displayLED(signature);
        Serial.println("Egg found");
        eggFound = true;
        return true;
      }
      
    
    
}

/*
 * resetBlocks() will reset all block information back to its starting value
 */
void resetBlocks() {
  x = initialNumber;
  y = initialNumber;
  width = initialNumber;
  height = initialNumber;
  egg = initialNumber;
  signature = initialNumber;
  ratioHW = initialNumber;
}

/*
 * isEggInRange() will use data from three IR sensors to determine whether
 * an egg is in range of the scoop. It returns true or false and also sets
 * eggInRange to true.
 */
bool isEggInRange() {

  int leftDistance = analogRead(leftDistanceIR);
  int rightDistance = analogRead(rightDistanceIR);
  int centerDistance = analogRead(centerDistanceIR);
  Serial.print("Is the ");
  switch (homeColor) {
    case 1:
      Serial.print("red ");
      break;
    case 2:
      Serial.print("orange ");
      break;
    case 3:
      Serial.print("yellow ");
      break;
    case 4:
      Serial.print("green ");
      break;
    case 5:
      break;
  }
  Serial.println("egg in range?");
  Serial.print("Left distance IR: ");

  Serial.println(leftDistance);
  Serial.print("Center distance IR: ");


  Serial.println(centerDistance);
  Serial.print("Right distance IR: ");

  Serial.println(rightDistance);

  if ((leftDistance > 200 && leftDistance < 515) ||
      (centerDistance > 375 && centerDistance < 630) ||
      (rightDistance > 380 && rightDistance < 680)) {
    Serial.println("The egg is within range");
    eggInRange = true;
    return true;
  }
  else {
    Serial.println("The egg is not within range");
    eggInRange = false;
    return false;
  }
}

void sortEggByColor(){
  uint16_t r, g, b, c, colorTemp, lux;
  sortTCS.getRawData(&r, &g, &b, &c);
  lux = sortTCS.calculateLux(r, g, b);
  
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.println(" ");
  
  eggColorCheck(r, g, b, lux);
}


void sortEgg(){
  sortEggByColor();
  while (eggColor != 0) {
    if (eggColor == homeColor) {
      keepEgg();
      eggsCollected++;
      sortEggByColor();
    } else if (eggColor != homeColor && eggColor != 5) {
      dumpEgg();
      sortEggByColor();
    } else if (eggColor == 5) {
      sortServo.write(120);
      delay(1000);
      sortServo.write(100);
      delay(1000);
      sortEggByColor();
    }
  }
  
//  if (eggColor != 0 && eggColor != 5){
//    if (eggColor == homeColor){
//      keepEgg();
//      eggsCollected ++;
//    }
//    else {
//      dumpEgg();
//    }
//  }
}


bool eggColorCheck(uint16_t red, uint16_t green, uint16_t blue, uint16_t lux) {
  eggColor = 0;
  
  if (lux >= 65000
      //red >= 0 && red <= 235 &&
      //green >= 0 && green <= 0 &&
      //blue >= 0 && blue <= 0
      ) {
      eggColor = 1;
      Serial.println("The sortRGB has seen RED Egg");
        return true;
  }
  else if (lux >= 0 && lux <= 200 &&
           red >= 400 && red <= 2000 &&
           green >= 100 && green <= 700 &&
           blue >= 100 && blue <= 400) {
    eggColor = 2;
    Serial.println("The sortRGB has seen Orange Egg");
    //delay(3000);
    return true;
  }
  else if (//lux >= 0 && lux <= 0 &&
           red >= 800 && red <= 2000 &&
           green >= 700 && green <= 2000 &&
           blue >= 400 && blue <= 1000) {
     eggColor = 3; 
    Serial.println("The sortRGB has seen YELLOW Egg");
    //delay(3000);
    return true;
  }
  else if (//lux >= 0 && lux <= 0 &&
           red >= 200 && red <= 480 &&
           //green >= 0 && green <= 0 &&
           blue >= 200 && blue <= 800) {

    eggColor = 4;
    Serial.println("The sortRGB has seen GREEN Egg");
    //delay(3000);
    return true;
  }
  
  else if (lux >= 0 && lux <= 75 &&
           red >= 70 && red <= 140 &&
           green >= 50 && green <= 110 &&
           blue >= 10 && blue <= 100) {
    eggColor = 0;
    Serial.println("The sortRGB sees NO Egg");
    //delay(3000);
    return false;
  }
  
  else {
    eggColor = 5;
    Serial.println("The RGB has seen an UNKNOWN color.");
    return false;
  }
}


