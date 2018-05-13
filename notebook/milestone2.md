# Milestone 2

## Drive towards a white boundary and stop before crossing it

This week, we learned how to solder from Larry. Esther created a second prototype chassis out of foamcore, since the first began to fall apart. Roger wrote the code for stopping the motors and Tyler wrote the code to turn the robot around. Roger fine-tuned the IR sensor when we realized that it was very sensitive and only worked at a specific height and angle. Finally, Esther and Tyler adjusted the height of the IR sensor appropriately.

Here is the new chassis in progress, thanks to Esther:
![New prototype from top angle](http://i38.photobucket.com/albums/e114/tykugler/secondPrototype_zpsjvrlwxsd.jpg)

Code snippet: 


``` 
// When the LED turns off, signalLED = HIGH, so the robot has encountered a white boundary. 
// Stop and turn around:
if(digitalRead(signalLED)) {
 
    // Brake both motors, decrease speed to 0
    digitalWrite(motorOneBrake, HIGH);
    digitalWrite(motorTwoBrake, HIGH);
    analogWrite(motorOneSpeed,0);
    analogWrite(motorTwoSpeed,0);
    Serial.print("STOP");
    delay(2000);

    // Turn around
    digitalWrite(motorOneBrake, LOW);
    digitalWrite(motorTwoBrake, LOW);
    digitalWrite(motorOne, LOW);          // motorOne is normally set to HIGH
    digitalWrite(motorTwo, LOW);          // so setting it to LOW makes it 
    analogWrite(motorOneSpeed, 120);      // turn the opposite direction
    analogWrite(motorTwoSpeed, 120);
    delay(1250);

    // Brake again, then move forward
    digitalWrite(motorOneBrake, HIGH);
    digitalWrite(motorTwoBrake, HIGH);
    analogWrite(motorOneSpeed, 0);
    analogWrite(motorTwoSpeed, 0);
    delay(1000);

    digitalWrite(motorOneBrake, LOW);
    digitalWrite(motorTwoBrake, LOW);
    digitalWrite(motorOne, HIGH); 
    digitalWrite(motorTwo, LOW); 
    analogWrite(motorOneSpeed, 120);    
    analogWrite(motorTwoSpeed, 120);
    delay(3000);
    
    }
```
Here are the old and new prototype side-by-side:
![Old and new prototype side-by-side](http://i38.photobucket.com/albums/e114/tykugler/prototypeSideBySide_zpsc7imfu6w.jpg)

Goals for next week:
We want to start working more with the Pixy cam, and investigate our robot's mobility issues. Currently, our robot has very clunky movements, due to a problem with one of the wheels/motors. 

### Acknowledgments

**Esther** designed the new body, and **Tyler** and **Roger** wrote the code.
