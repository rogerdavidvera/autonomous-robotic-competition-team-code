/*************************************************************
Group C: Tyler Kugler, Roger Vera, Esther Xu
Milestone 5 -- Basic motor movements
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
  digitalWrite(directionRight, HIGH);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(500);
}

void rightTurn() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, HIGH);
  digitalWrite(directionRight, LOW);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(500);
}

void slightLeftTurn() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, LOW);
  digitalWrite(directionRight, HIGH);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(250);
  
}

void slightRightTurn() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, HIGH);
  digitalWrite(directionRight, LOW);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(250);
  
}

void spin() {
  digitalWrite(brakeLeft, LOW);
  digitalWrite(brakeRight, LOW);
  digitalWrite(directionLeft, LOW);
  digitalWrite(directionRight, HIGH);
  analogWrite(motorLeft, normalSpeed);
  analogWrite(motorRight, normalSpeed);
  delay(1000); 
}


