# Milestone 8

## Find an egg that matches your starting color and bring it back to your home quadrant

This milestone was... rough. It is easily the most important milestone -- the others certainly built up to this, but it is impossible to do well in the competition if our robot can't do this. And unfortunately, it took us quite a while to get there. This entire semester, our group was very ambitious. The other groups around us kept things very simple: find an egg, and push it around to where it needs to go. But that's boring! And inefficient! It's simply safer from a competitive standpoint to capture eggs and hoard them within the robot's body. 

Our initial idea for capturing eggs was to have two arms that would lower to the ground and then clap together, trapping the egg. They would then lift back up and dump the egg into a bucket that would sort it. More reasoning on that and our goals during the competition later. Anyway, this worked in theory perfectly. An IR sensor was perfect for detecting the right distance, and the arms always clapped together wonderfully. Before we could test it further, though, we needed to perfect our egg tracking method. 

![Clapper Ovi](http://i38.photobucket.com/albums/e114/tykugler/IMG_3559_zpsptoqjbjw.jpg)

In order to track the egg, we kept it simple. Tyler wrote a function that adjusted the speed of the left and right motors dependent on the x position of the egg returned by our eggSearch method. And this worked rather well. The only time when this method under-performed was when the egg was too close to the robot to begin with. Since we can't adjust toward the egg at a snail's pace due to a minimum speed requirement, we just decided to take the loss on that front. Since our strategy is to loop around the track, it'll be fine if we miss an egg once or twice because we'll get back around to it quickly enough. 

``` C
/*
 * moveTowardEgg() will move dynamically toward the egg
 * using information from the pixy camera
 */
void moveTowardEgg() {
  if (x == initialNumber) {
    forward();
  }
  else {
  leftSpeed = (0.375 * x) + 80;
  rightSpeed = 211 - (0.375 * x);
  forward();
  }
}
```

Unfortunately, this is where we ran into trouble. By using an IR sensor with these clapping arms, we restricted our egg-catching ability to one singular point in space. Our egg tracking simply isn't good enough for that.  So we adapted. Esther came up with an incredible idea. It's incredibly complex -- words can't do it justice. So here's a video:

[Ovi tracking and picking up an egg -- Click to watch!](https://vimeo.com/216949549)

Ovi can now grab eggs that land in a square range. A foamcore board pushes it forward, into range of a scoop which twists, capturing the egg. Then two arms lift the egg into a container, securing the egg. You'll notice quite a difference in design between Clapper Ovi and Scooper Ovi. Since we failed 4 consecutive milestones, there was quite a lot of time to develop new ideas. We have reasons for these changes, and we'll explain them a bit more in the next few notebook entries.

All that was left to do was return home after grabbing it.  We use a boundarySearch method written by Tyler and Esther which determines the color from RGB sensors (whose data was gathered meticulously by Roger!). We set the current quadrant and last quadrant based on a mapping system. Our home quadrant is always A, and we set the other colors to their quadrant in counterclockwise order from A. So if red is A, yellow will be B, orange is C, and green is D. By doing this kind of mapping, we can always get to our home quadrant based on a combination of general movements and repeated boundary searches until we reach quadrant A again. For example, if Ovi moves from C to B, Ovi will choose to arc to the right while searching for the boundary. From there, the next boundary will be from B to A, bringing Ovi to home. 

### Acknowledgments
**Esther** created the mechanism which picks up eggs. **Tyler** wrote the code for egg tracking and boundary searching. **Roger** gathered all of the RGB data for the boundary search.
