/* 
 * COMPETITION CODE
 * OVIRAPTORS: Esther Xu, Roger Vera, Tyler Kugler
 * SERVO FUNCTIONS
 */

/*
 * armsUp() returns the arms to their resting position
 */
void armsUp() {
  rightArm.write(70);    // Neutral Position
  leftArm.write(120);    // Neutral Position
}

/*
 * armsDown() lowers the arms to the ground for the purpose
 * of scooping an egg
 */
void armsDown() {
  rightArm.write(170);  // Down position
  leftArm.write(20);    // Down position
}

/*
 * repositionEgg()
 * lower the arms and push the wall up against
 * the scoop
 */
void repositionEgg() {
  stopMovement();
  scoopServo.write(50);  // Neutral Position
  delay(1000);
  armsDown();
  delay(1000);
  scoopServo.write(80);
  pushWall();
}

/*
 * scoopEgg() will scoop the egg and lift the arms 
 * and then pull the wall
 */
void scoopEgg() {
  scoopServo.write(180); // Scoop Movement
  delay(1000);
  armsUp();
  delay(1000);
  pullWall();
}

/*
 * pushWall() brings the wall away from the scoop
 */
void pushWall() {
  for (int i = 1; i < 100; i++) {
    leftWallServo.write(80 + i);
    rightWallServo.write(100 - i);
    delay(30);
  }
}

/*
 * pullWall() returns the wall to its position against
 * the scoop. This action will push eggs between the wall
 * and scoop into the scoop
 */
void pullWall() {
  for (int i = 1; i < 100; i++) {
    leftWallServo.write(180 - i);
    rightWallServo.write(i);
    delay(30);
  }
}

void dumpEgg(){
  sortServo.write(150);
  delay(1000);
  sortServo.write(110);
  delay(1000);
}

void keepEgg(){
  sortServo.write(30);
  delay(1000);
  sortServo.write(110);
  delay(1000);
}
