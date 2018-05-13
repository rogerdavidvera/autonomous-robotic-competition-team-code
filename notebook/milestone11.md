# Milestone 11

## Score more than 3 points in a 1v1 round

Another failure, unfortunately. A solemn way to end the semester, certainly! By random chance, we placed second in the competition, which is incredible. However, we really believed in our robot and the fact that we weren't able to deliver on the milestones is a real bummer. 

We've spent the past 2 journals chronicling our failures, and we're not really eager to spend more time thinking about it. So we'll keep it short this time: perhaps our biggest failure was our inability to budget time effectively and determine how long testing would take. 

The best example is the most humiliating, so give us props for #exposing ourselves right now. Let us lay the scene: It's 7pm on Sunday, May 14th. We've just completed milestones 4 and 8, two milestones we failed a long time ago. We're feeling on top of the world -- we can _do_ this! And we got cocky. Esther wrote pseudocode for clearing out our home quadrant after we returned home with our 3 eggs, and Tyler began writing code for clearing those eggs. That was the most fun we had that night; Ovi was capable of scooping eggs, lifting them, and instead of depositing them in the scoop, **LAUNCHING** them several feet away by dropping the arms quickly.

``` C
void holdEgg(){
  // There is a series of for-loops to prevent the egg from slipping out of the 
  // scoop/wall combination prematurely. These for-loops allow for the egg to be
  // smoothly lifted upward before it is LAUNCHED when Ovi reaches a boder
  scoopServo.write(140); //Scoop
  delay(1000);
  for (int i = 0; i < 60; i++) {
    rightArm.write(170 - i);
    leftArm.write(20 + i);
    delay(30);
  }
  delay(500);
  scoopServo.write(120);
  delay(1000);
  for (int i = 0; i < 20; i++) {
    rightArm.write(110 - i);
    leftArm.write(80 + i);
    scoopServo.write(120 - i);
    delay(30);
  }
  delay(500);
  scoopServo.write(80);
  delay(1000);
  for (int i = 0; i < 20; i++) {
    rightArm.write(90 - i);
    leftArm.write(100 + i);
    delay(30);
  }
  delay(500);
}
void launchEgg(){
  rightArm.write(140);
  leftArm.write(50);
  delay(1000);
  armsUp();
  pullWall();
}
```

Knowing now that we needed just 2-3 more hours before the competition to perfect our angles & color values, wow. What a waste of time! We became way too confident and definitely learned our lesson the hard way. 

But who on _Earth_ wants to end on a salty note? Not us! If we're the Oviraptors and the meteor is hurtling toward Earth, let's have some fun and be nostalgic for a hot second before that meteor exterminates us! Let's talk about the iconic sorting servo. 

It was Esther's brainchild and addressed Ovi's greatest weakness. When Ovi runs eggSearch, he's looking for a specific egg, and moves toward that egg until it's in range, as determined by IR sensors. By these sensors do not work in unison -- _any_ egg can trigger the IR sensor, which led to a lot of false positives. The solution? Sort the eggs! So we swapped our container from a huge platform to a funnel that forces eggs into a sorter. You'll have to forgive the cardboard and legos; we left the 3D printing and cute designs to the groups who went with _simpler_ designs. 

![Ovi's funnel](http://i38.photobucket.com/albums/e114/tykugler/IMG_3571_zps431nliui.jpg)

From there, an RGB sensor reads the color of an egg which is in the sorter. If the egg matches our home color, we sort it to the left into our container for permanent storage. If it doesn't, we sort it to the right, where it is immediately deposited behind us. [Check out this video of it in action here, featuring Roger acting as the arm servos and Esther's giddy giggles.](https://vimeo.com/217432850)

Our robot may not work like we intended it to, but it's definitely the coolest. 

### Acknowledgments
**Esther**'s incredible designs set us above the others. While they aren't aesthetically pleasing, they certainly are a feat of engineering. **Tyler**'s boundary searching and egg tracking brought us within _inches_ of victory. **Roger** was the glue that kept the group from falling apart, and that should not be taken lightly. Esther and Tyler come from very different standpoints, and Roger brought them together. We didn't win, but our group did some incredible work.
