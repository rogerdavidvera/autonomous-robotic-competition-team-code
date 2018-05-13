# Milestone 7

## Find home

Milestone 7 is the last of the milestones prior to our final body design. As a result, the robot's movement and general functioning is rudimentary and somewhat unpractical. Nevertheless, our RGB sensor successfully picks up the color boundaries at a low speed/delay. Our goal for next week is to have the first iteration of our final design, attach more RGB sensors to have more fluid recognition of boundary lines, and ensure the robot moves relatively straight.

``` C
    spin(); // Spin around completely
    slightLeftTurn(); // Adjust a bit
    stopMovement();
    while (quadrant != homebase) { // While it has not detected homebase again
      boundarySearch();
      forward();
      delay(40);
      stopMovement();
      delay(40);
    } // Found homebase
    forward(); // Get into gray area
    delay(1500);
    stopMovement(); // Stop for 120 seconds,2 minutes
```
    
In this part of the code, the robot has already moved across the boundary once. First, it will spin, then approach the line it just crossed. It will call boundarySearch() until the RGB finds the color that matches the homebase color (the one detected when crossing the line the first time). After finding it, it will move forward and then stop. 

![Current iteration of body](http://i38.photobucket.com/albums/e114/tykugler/Image-1%202_zpsiayenvln.jpg)

### Acknowledgments
**Esther** created the body and tweaked it when there were extreme mobility issues. **Roger** collected the data for the boundary search, and **Tyler** wrote the algorithm for the boundary search.
