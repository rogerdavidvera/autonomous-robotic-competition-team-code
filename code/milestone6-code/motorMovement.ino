/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 6 -- Basic motor movements
*************************************************************/

void forward() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, HIGH);
  digitalWrite(directionRight, LOW);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
}

void reverse() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, LOW);
  digitalWrite(directionRight, HIGH);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
}

void stopMovement() {
  digitalWrite(brakeLeft, HIGH);
  digitalWrite(brakeRight, HIGH);
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
}

void leftTurn() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, LOW);
  digitalWrite(directionRight, LOW);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(500);
  stopMovement();
}

void rightTurn() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, HIGH);
  digitalWrite(directionRight, HIGH);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(500);
  stopMovement();
}

void slightRightTurn() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, LOW);
  digitalWrite(directionRight, LOW);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(150);
  stopMovement();
  
}

void slightLeftTurn() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, LOW);
  digitalWrite(directionRight, LOW);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(80);
  stopMovement();
  delay(1000);
}

void spin() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, LOW);
  digitalWrite(directionRight, LOW);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(1000); 
  stopMovement();
}
