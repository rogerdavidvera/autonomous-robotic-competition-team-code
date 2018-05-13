# Milestone 6

## Move an egg out of bounds

Last week, we proved that our robot can move around the arena and detect an egg. This week, we built on that and showed that our robot can approach an egg and then move it out of bounds. Since our robot can already detect eggs, the main task for the robot this week was to approach the egg. This is easier said than done. Because the egg may not be directly in front of the robot when the robot detects the egg, moving forward alone is not good enough. Eventually the robot would lose the egg when it falls out of view on the right or left. 

A better approach would be to find the egg, then turn left or right appropriately until the egg is centered in front of the robot. Then it's an easy task to move forward until the egg is close enough. However, this too is suboptimal. It would get the job done, but wastes precious time turning to get the angle perfectly. In a real competition setting, the egg may be stolen by a competitor while our robot attempts to get everything *just* right.

![Esther's explanation of dynamic forward movement](http://i38.photobucket.com/albums/e114/tykugler/IMG_3376_zpsp0q3qhab.jpg)
 
Professor de Leeuw introduced us to a more interesting idea: dynamic forward motion. Instead of having the robot turn and then move, our robot should turn while moving. Esther drew up some plans for how we could accomplish that. Tyler wrote the code, altering our forward() method. The previous version moved the motors at a predetermined normalSpeed. In the new version, the left and right motors move forward at the normalSpeed plus a left/right modifier. When the object is left of center, the right motor speeds up slightly. When the object is right of center, the opposite happens. 

Unfortunately, due to time constraints, we were *unable* to perfect this strategy for this milestone. We decided to use the second strategy, and modified our existing code so that only eggs in the very center of the camera view would satisfy our eggSearch() method. This allowed us to drop an arm down to the ground and capture the egg as soon as the robot moved forward. 

``` C
   // Move left to find eggs that are in center of view

   servoArm.write(180);
   
   while (!eggFound) {
    Serial.println("Moving Left");
    slightLeftTurn();
    Serial.println("Calling EggSearch");
    eggSearch();
   }


  // Move forward with egg until out of boundaries
  
  if (eggFound) {         // AKA Egg is FOUND
    Serial.println("Moving forward");
    servoArm.write(85);
    forward();
    delay(60000);        // Move forward for a minute 
    stopMovement();
  }
  ```

### Acknowledgments
**Esther** designed the body, **Roger** fine-tuned the pixy so that Ovi finds eggs efficiently, and **Tyler** wrote the code for finding and approaching an egg
