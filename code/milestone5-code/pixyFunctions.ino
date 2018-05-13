/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 5 -- Pixy cam functions
*************************************************************/

void eggSearch() {

    Serial.println("Calling getBlocks");
    blocks = pixy.getBlocks();
    Serial.print("Number of blocks returned: ");
    Serial.println(blocks);
    Serial.println();

  int attempts = 0;
  while (attempts < 20 && !blocks) {
    Serial.println("Calling getBlocks");
    Serial.print("Attempt Number: ");
    Serial.println(attempts);
    Serial.print("Number of blocks returned: ");
    Serial.println(blocks);
    blocks = pixy.getBlocks();
    attempts++;
  }

  // resetting block values
  resetBlockInfo();

  if (blocks) {
    for (j=0; j < blocks; j++) {
        h = pixy.blocks[j].height;
        w = pixy.blocks[j].width;
        int yCoor = pixy.blocks[j].y;
        ratioHW = h/w;
          
      // signature must equal quadrant and width-height ratio must be <= 2
      if (/*(quadrant == pixy.blocks[j].signature) && */ ((ratioHW > 0.90) || (yCoor < 160))) {
            
          // if there is no current egg, make j = egg
          if (egg == initialNum) {
            egg = j;        
            x = pixy.blocks[egg].x;
            y = pixy.blocks[egg].y;
            width = pixy.blocks[egg].width;
            height = pixy.blocks[egg].height;
            sig = pixy.blocks[egg].signature;
            h = pixy.blocks[egg].height;
            w = pixy.blocks[egg].width;
            ratioHW = h/w;
          } 
          
          else if ((pixy.blocks[j].height > pixy.blocks[egg].height) && 
                      (pixy.blocks[j].width > pixy.blocks[egg].width)) {
            egg = j;
            x = pixy.blocks[egg].x;
            y = pixy.blocks[egg].y;
            width = pixy.blocks[egg].width;
            height = pixy.blocks[egg].height;
            sig = pixy.blocks[egg].signature;
            h = pixy.blocks[egg].height;
            w = pixy.blocks[egg].width;
            ratioHW = h/w;
          }
      }
          
      if (egg == initialNum) {
        Serial.println("No egg found.");
      }
      
      else {
        Serial.println("Egg found!\n");
        for (int i = 0; i < 10; i++) {
           blinkLED(quadrant);       
        }
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
  ratioHW = initialNum;
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

  Serial.print("H is: ");
  Serial.println(h);
  
  Serial.print("W is: ");
  Serial.println(w);
  
  Serial.print("Height:Width ratio is: ");
  Serial.println(ratioHW);
  Serial.println("\n");
}
