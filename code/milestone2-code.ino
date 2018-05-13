/*************************************************************
Team C Milestone 2
by Roger Vera, Tyler Kugler, Esther Xu
*************************************************************/
int motorOne = 12;
int motorOneBrake = 9;
int motorOneSpeed = 3;

int motorTwo = 13;
int motorTwoBrake = 8;
int motorTwoSpeed = 11;

int signalLED = 53;

void setup() {

  Serial.begin(9600);

  //Setting up motorOne
  pinMode(motorOne, OUTPUT);        //Initiates motorOne pin
  pinMode(motorOneBrake, OUTPUT);   //Initiates motorOneBrake pin

  // Setting up motorTwo
  pinMode(motorTwo, OUTPUT);        //Initiates motorTwo pin
  pinMode(motorTwoBrake, OUTPUT);   //Initiates motorTwoBrake pin
  
  // Setting up LED input for white boundary detection
  pinMode(signalLED, INPUT);        //Initiates signalLED pin
}

void loop(){
  
    Serial.println(digitalRead(signalLED));
    
  if(digitalRead(signalLED)) {
    Serial.println("LED is off, white boundary detected");
  
    
    // Brake both motors, decrease speed to 0
    digitalWrite(motorOneBrake, HIGH);
    digitalWrite(motorTwoBrake, HIGH);
    analogWrite(motorOneSpeed,0);
    analogWrite(motorTwoSpeed,0);
    Serial.print("STOPPING");
    delay(10000);
    
    // Turn around
    digitalWrite(motorOneBrake, LOW);
    digitalWrite(motorTwoBrake, LOW);
    digitalWrite(motorOne, LOW);          // motorOne is normally set to HIGH
    digitalWrite(motorTwo, LOW);          // so setting it to LOW makes it 
    analogWrite(motorOneSpeed, 120);      // turn the opposite direction
    analogWrite(motorTwoSpeed, 120);
    Serial.print("TURNING");
    delay(1250);

    // Brake again, then move forward
    digitalWrite(motorOneBrake, HIGH);
    digitalWrite(motorTwoBrake, HIGH);
    analogWrite(motorOneSpeed, 0);
    analogWrite(motorTwoSpeed, 0);
    Serial.print("STOPPING);
    delay(1000);

    digitalWrite(motorOneBrake, LOW);
    digitalWrite(motorTwoBrake, LOW);
    digitalWrite(motorOne, HIGH); 
    digitalWrite(motorTwo, LOW); 
    analogWrite(motorOneSpeed, 120);    
    analogWrite(motorTwoSpeed, 120);
    delay(3000);
  
  }
  else {
    Serial.println("LED is on, no white boundary detected");
  
    
    // motorOne forward 
    digitalWrite(motorOne, HIGH);       //Establishes forward direction of Channel A
    digitalWrite(motorOneBrake, LOW);   //Disengage the Brake for Channel A
    analogWrite(motorOneSpeed, 120);    //Spins the motor on Channel A at half speed

    // motorTwo backward 
    digitalWrite(motorTwo, LOW);        //Establishes backward direction of Channel B
    digitalWrite(motorTwoBrake, LOW);   //Disengage the Brake for Channel B
    analogWrite(motorTwoSpeed, 120);    //Spins the motor on Channel B at half speed
 
  }

}
