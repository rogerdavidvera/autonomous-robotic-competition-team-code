# Milestone 3

## Signal starting quadrant

This week, Esther focused on streamlining the robot chassis, Tyler worked on the code, and Roger perfected the object detection. Esther designed a small foamcore container for the Arduino and motor shield rather than placing it sideways into a compartment of the chassis. Sitting flat, it is much easier to connect the motors, breadboard, and battery to it. The compartment sits flush with the top of the chassis as we decided this is the most ideal location given the lengths of wires we did not want to extend without good reason. 

The Pixy camera is built to learn new color signatures rather easily, but Roger spent hours fine-tuning the parameters for our purposes. The Pixy camera normally returns as many objects as it finds, but he tweaked it so that only the closest object is returned. Looking at a 2D image of a 3D surface, the closest object would be the one with the lowest y coordinate. Roger also worked with the servo motors when we reached a problem with the DC motors. The pixy camera and DC motor sent mixed signals to each other, causing both to malfunction. 

![Pixy cam image](http://i38.photobucket.com/albums/e114/tykugler/pixycamimage_zps4wyumcma.jpg)

Tyler wrote the code to accomplish this week's task. The team agreed that the robot should turn 45 degrees and then move slightly forward to increase the likelihood of detecting the correct object signature. Tyler rewrote the motor code to make it work with servo motors instead. He also wrote the code that analyzed the Pixy data. When a block is found, it has a corresponding signature describing the color code of the object. These codes are in octal with 1=red, 2=orange, 3=yellow, and 4=green, so an object with signature 14 is a red and green object. However, when this information is given back to the program, it is returned in decimal format (eg. signature 14 becomes 12, signature 23 becomes 19, etc).The blocks also have an angle. When the angle is positive, the first digit in the signature is the color closer to the camera; when the angle is negative, the second digit is the closer color. The cases can be separated by using a switch that takes in the signatures, and then using the angles case-by-case to determine the closer color. 

![Serial monitor image](http://i38.photobucket.com/albums/e114/tykugler/Screen%20Shot%202017-02-15%20at%204.32.06%20PM_zpsakq5nyzq.png)

```
void determineClosest(int signature, int angle) {

// for the LED colors, 1 = red, 2 = orange, 3 = yellow, 4 = green, 5 = an error has been reached

   switch(signature) {
    case 1:
    case 2:
    case 3:
    case 4:
      ledColor = 5;
      break;
    case 10:
    case 11:
    case 12:
      if (angle >= 0) {
        ledColor = 1;
      }
      else {
        ledColor = signature - 8;
      }
      break;
    case 19:
    case 20:
      if (angle >= 0) {
        ledColor = 2;
      }
      else {
        ledColor = signature - 16;
      }
      break;
    case 28:
      if (angle >= 0) {
        ledColor = 3;
      }
      else {
        ledColor = 4;
      }
      break;
    default:
      ledColor = 5;
      break;
   }
}
```

### Trouble in paradise!

Eventually, our group decided that the servo motors weren't going to be work, at least for this milestone. Sometimes the best solution to a problem is an unconventional one. Instead of moving the robot closer to the boundaries, we added a long arm to our robot which held the Pixy at the perfect distance for object detection. While it's clear that our final robot will move around the arena, our current prototype is completely stationary. 

Esther was invaluable in achieving our new design of the robot when we decided that our robot was going to be stationary for this milestone. Esther designed a long arm that would hold the Pixy at the perfect angle and distance from the boundary. She also researched how to light up various LEDs for the purpose of displaying which color is the closest. 

![Robot ft. Giraffe neck](http://i38.photobucket.com/albums/e114/tykugler/giraffe_zpsvqshudsy.jpg)

### Acknowledgments

To master the LED lights, we used the USK guide code for reference

**Esther** designed the body, including the giraffe neck :) **Roger** worked with the pixy cam values for boundary detection. **Tyler** wrote the code.

