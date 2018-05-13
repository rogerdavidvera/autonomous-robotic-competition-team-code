/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 5 -- Pixy cam functions
*************************************************************/

void eggSearch() {

  Serial.println("Calling getBlocks");
  blocks = pixy.getBlocks();
  Serial.println("Blocks returned");

  // resetting block values
  resetBlockInfo();

  if (blocks) {
    for (j=0; j < blocks; j++) {
      
      // if the angle is not zero, disregard
      if (pixy.blocks[j].angle != 0) {
          continue;
          }
          
      // signature must equal quadrant and width-height ratio must be <= 2
      if ((quadrant == pixy.blocks[j].signature) && 
          (pixy.blocks[j].width / pixy.blocks[j].height) <= 2) {
            
          // if there is no current egg, make j = egg
          if (egg == initialNum) {
              egg = j;
              }
              
          // if there is already a current egg, store the larger one
          else if ((pixy.blocks[j].height > pixy.blocks[egg].height)
                  && pixy.blocks[j].width > pixy.blocks[egg].width) {
              egg = j;
              }
          }
          
      if (egg == initialNum) {
        Serial.println("No egg found.");
      }
      
      else {
        Serial.println("Egg found!");
        x = pixy.blocks[j].x;
        y = pixy.blocks[j].y;
        width = pixy.blocks[j].width;
        height = pixy.blocks[j].height;
        area = width * height;
        sig = pixy.blocks[j].signature;
      }
    }
  }
  
}

void resetBlockInfo() {
  x = initialNum;
  y = initialNum;
  width = initialNum;
  height = initialNum;
  egg = initialNum;
  sig = initialNum;
  area = initialNum;
}

void printValues() {
  Serial.print("Signature is: ");
  Serial.println(sig);
  
  Serial.print("X is: ");
  Serial.println(x);
  
  Serial.print("Y is: ");
  Serial.println(y);
  
  Serial.print("Width is: ");
  Serial.println(width);
  
  Serial.print("Height is: ");
  Serial.println(height);
  
  Serial.print("Area is: ");
  Serial.print(area);
}

