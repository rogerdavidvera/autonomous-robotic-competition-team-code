# Milestone 1
## Start in a quadrant, exit the quadrant

  We accomplished this in three steps. The first step was the code. 
Roger and Tyler sifted through various references by Arduino about how to make DC motors spin, before eventually choosing one and using it for this milestone. 
It is cited in the code uploaded and below. Meanwhile, Esther completed the second task: creating a prototype body. 
She sketched a design on scrap paper, traced it onto foamcore, and cut out the pieces using a box cutter. 
Esther put the individual pieces together using duct tape. 
Finally, the three of us accomplished the third task together: wiring the motor shield and putting all of the pieces together. 
Our first prototype has two wheels attached to two motors whose wires connect through a hole in the bottom of the foamcore cart. 
These wires connect to the motor shield, which lies in the cart. 
Connected to the motor shield is the battery, which lies directly on top of the motor shield. 
Finally, we added a lego wheel on the back for stability. 

Click below to watch a video of the robot moving:
[![Robot moving](http://oi68.tinypic.com/2gtrrbs.jpg)](https://vimeo.com/202575368 "Robot moving - Click to Watch!")

### Code:
```
void setup() {

  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin

}

void loop(){


  //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B backward @ full speed
  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);    //Spins the motor on Channel B at full speed

}
```

pinMode initiates motor and brake channels, digitalWrite establishes the forward direction and disengages the brakes, and analogWrite determines the speed at which the motor spins. For motor A, choosing HIGH makes the wheel go forward. But for motor B, it must be LOW because of the orientation of the wheel. Since motor B is facing the opposite direction, the motor must spin the opposite direction in order to move forward with motor A. 

### Acknowledgements: 
Motor Shield 2-Channel DC Motor Demo:
https://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

**Roger** and **Tyler** adapted the code they found online; **Esther** designed the body.
