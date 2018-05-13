/* 
 * COMPETITION CODE
 * OVIRAPTORS: Esther Xu, Roger Vera, Tyler Kugler
 * MOTOR FUNCTIONS
 */

/*
 * forward() will move the robot forward at the designated speed
 * increasing leftSpeed will cause the robot to turn right
 * increasing rightSpeed will cause the robot to left left
 */
 void forward() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, leftForward);
  digitalWrite(directionRight, rightForward);
  analogWrite(motorLeft, leftSpeed);
  analogWrite(motorRight, rightSpeed);
}

/*
 * reverse() will move the robot backwards at normal speed
 */
void reverse() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, leftBackward);
  digitalWrite(directionRight, rightBackward);
  analogWrite(motorLeft, leftNormalSpeed);
  analogWrite(motorRight, rightNormalSpeed);
}

/*
 * stopMovement() stops the robot's movement until a new
 * movement function is called
 */
void stopMovement() {
  digitalWrite(brakeLeft, HIGH);
  digitalWrite(brakeRight, HIGH);
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
}

/*
 * spin() spins the robot in a half turn and then stops
 */
void spin() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, leftBackward);
  digitalWrite(directionRight, rightForward);
  analogWrite(motorLeft, leftNormalSpeed + 100);
  analogWrite(motorRight, rightNormalSpeed + 100);
  delay(500);
  stopMovement();
  delay(100);
}

void spinHome(){
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, leftBackward);
  digitalWrite(directionRight, rightForward);
  analogWrite(motorLeft, leftNormalSpeed + 100);
  analogWrite(motorRight, rightNormalSpeed + 100);
  delay(900);
  stopMovement();
  delay(100);
}

void spinFortyFive(){
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, leftForward);
  digitalWrite(directionRight, rightBackward);
  analogWrite(motorLeft, leftNormalSpeed + 100);
  analogWrite(motorRight, rightNormalSpeed + 100);
  delay(250);
  stopMovement();
  delay(100);
}

/*
 * stepForward() will move Ovi slightly forward and then stop
 */
void stepForward() {
  leftSpeed = leftNormalSpeed;
  rightSpeed = rightNormalSpeed;
  forward();
  delay(100);
  stopMovement();
  delay(200);
}

/*
 * stepForward() will move Ovi slightly forward and then stop
 */
void stepBackward() {
  reverse();
  delay(100);
  stopMovement();
  delay(200);
}

/* 
 *  arcLeft() will cause the robot to move in an arc 
 *  to the left
 */
void arcLeft() {
  leftSpeed = leftNormalSpeed;
  rightSpeed = rightNormalSpeed * 1.25;
  forward();
}

void slightArcLeft(){
  leftSpeed = leftNormalSpeed * 0.88;
  rightSpeed = rightNormalSpeed * 1.12;
  forward();
}

/* 
 *  arcRight() will cause the robot to move in an arc
 *  to the right
 */
void arcRight() {
  leftSpeed = leftNormalSpeed * 1.1;
  rightSpeed = rightNormalSpeed;
  forward();
}

void slightArcRight() {
  leftSpeed = leftNormalSpeed * 1.1;
  rightSpeed = rightNormalSpeed * 0.9;
  forward();
}

/*
 * escapeWhiteLine() will cause the robot to spin then
 * move forward as it was before
 */
void escapeWhiteLine() {
  stopMovement();
  delay(20);
  reverse();
  delay(1000);
  stopMovement();
  spin();
  //forward();
  //delay(500);
}

/*
 * moveTowardEgg() will move dynamically toward the egg
 * using information from the pixy camera
 */
void moveTowardEgg() {
  if (x == initialNumber) {
    forward();
  }
  else {
  //leftSpeed = (0.375 * x) + 80;
  //rightSpeed = 200 - (0.375 * x);
  leftSpeed = (0.375 * x) + 80;
  rightSpeed = 200 - (0.375 * x);
  forward();
}
}

/*
 * searchForHome() will move roughly in the direction of home
 * this is dependent on the latest information, so the direction 
 * may be wrong. this will correct itself at the next boundary found
 */
 
 void goHome() {
//  switch(currentQuadrant) {
//    case 'A':                             // Ovi is probably at home, roam around to be sure
//      forward();
//      break;
//    case 'B':
//      if (lastQuadrant == 'A') {          // Ovi is probably in B and came from A, so spin
//        spin();
//        currentQuadrant = 'A';
//        lastQuadrant = 'B';
//        forward();
//      }
//      else {                              // Ovi is probably in B and came from C, so arc right
//        arcRight();
//      }
//      break;
//    case 'C':
//      if (lastQuadrant == 'B') {          // Ovi is probably in C and came from B, so arc left
//        arcLeft();
//        currentQuadrant = 'B';
//        lastQuadrant = 'C';
//      }
//      else {                              // Ovi is probably in C and came from D, so arc right
//        currentQuadrant = 'D';
//        lastQuadrant = 'C';
//        arcRight();
//      }
//      break;
//    case 'D':
//      if (lastQuadrant == 'A') {          // Ovi is probably in D and came from A, so spin
//        spin();
//        currentQuadrant = 'A';
//        lastQuadrant = 'D';
//        forward();
//      }
//      else {                              // Ovi is probably in D and came from C, so arc left
//        arcLeft();
//      }
//  }
    if (homeDirection() == 1){
      arcLeft();
      Serial.println("Going left");
    }
    else if (homeDirection() == 2){
      arcRight();
      Serial.println("Going right");
    }
    else {
      forward();
      Serial.println("Going forward");
    }
 }



