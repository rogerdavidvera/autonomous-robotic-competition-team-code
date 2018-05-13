# Milestone 4

## Find an egg that matches the starting quadrant color

This week's milestone was pretty tricky. We began by outlining a strategy for how the robot should act. This is what we decided:
  1. Never cross a white boundary
  2. Find the starting quadrant using an RGB sensor
  3. Search for an egg whose signature matches the starting quadrant
  4. Depending on the X position of the egg as detected by the Pixy cam, turn left, right, or move straight ahead.
  5. When the area of the egg reaches a certain size, stop.
  
Roger did research and tested out using RGB and Lux sensors to detect the quadrant boundary. Esther had to redesign the robot, which unfortunately meant cutting off the last prototype's giraffe neck! Tyler wrote the code for interpreting the block results from the Pixy cam and acting upon that information.

``` C++
switch(caseNumber) {
   . . . . . 
    // Case 2: SEARCH FOR CORRESPONDING EGG.
    case 2: 
      slightRight(); 
      forwardMovement();
      delay(100);
      stopMovement();
      eggSearch(blocks);
      break;
      
    // Case 3: FOUND AN EGG. TURN TOWARD IT.
    case 3:
      eggSearch(blocks);
        // egg lost, return to case 2
      if (correspondingEgg = 500 && x == 500) {
        caseNumber = 2;
        break;
      }
        // egg is centered, go to case 4
      else if (x >= 130 && x <= 190) {
        caseNumber = 4;
      }
        // egg is left of center, turn left 
      else if (x > 190) {
        slightLeft();
        break;
      }
        // egg is right of center, turn right
      else {
        slightRight();
        break;
      }
   . . . . .
   }
```

Unfortunately, despite putting in hours (and in the case of Esther and Roger, an all-nighter), we were unable to pass this milestone for full credit. Due to the imprecise nature of continuous servos moving at different speeds, our robot could not make a complete stop. This meant that tracking the egg and making slight lefts and rights to approach the egg was impossible. However, we don't leave this week feeling totally defeated. We were able to successfully implement an RGB sensor for boundary detection, our morphology is really coming along, and the code for detecting the eggs worked except for the movement. This upcoming spring break will give us a chance to regroup and get back on track for the next milestone! 

![New mount for the pixy cam; now closer to ground](http://i38.photobucket.com/albums/e114/tykugler/IMG_3272_zpsgvccmqmv.jpg)
![Robot from above](http://i38.photobucket.com/albums/e114/tykugler/IMG_3275_zps2nsqodxh.jpg)

### Acknowledgments
**Esther** designed the body and taught us about continuous servos. **Roger** worked on RGB sensor values. **Tyler** wrote the code for the milestone. 
