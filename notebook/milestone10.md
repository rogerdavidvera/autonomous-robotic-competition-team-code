# Milestone 10 

## Score more than 3 points in a solo round. 

YIKES. We failed this milestone, too. It should be clear that the main reason is our dreadful method for searching the arena. Arcing left and praying that Ovi would magically see all of the eggs was shooting for the stars. In practice, it totally worked -- our pixy was configured excellently. During the competition, however, the lighting and setting totally wrecked us. No excuses, though; we should have seen that coming and prepared a bit better for different lighting scenarios. 

We never gave ourselves time to perfect our searching method due to one eternal pain-in-the-neck: our **boundarySearch**. Here’s our method for detecting color boundaries:

1. Run boundaryTrigger(). 
* If any color is found by either RGB sensor, call boundarySearch().
2. Run boundarySearch(). 
* Reverse slightly, then step forward until a color is found. That is the quadrant Ovi is exiting, _lastQuadrant_
* Move forward slightly, then step backward until a color is found. The is the quadrant Ovi is entering, _currentQuadrant_
* Move forward normally, having saved these new quadrants

And it works! It works wonderfully. But it came at a cost. We simply spent too much time on our boundarySearch during the semester. We’ve been working on it since week 3, when we started with a pixy cam (plus that horrific giraffe neck because our motors weren’t cooperating with the pixy cam!) instead of an RGB. We’re come so, so, SO far since then. We’ve tested approximately 4 different algorithms, varying our strategy. And believe us, we tried EVERYTHING: stepping slowly forward, smoothly & slowly going forward, smoothly going forward and then backward for the second boundary, and then finally our current method, which combines the step-method with the forward-reverse method. 

As for the actual RGB values we use to determine the color, it’s been a rollercoaster. Roger spent hours upon hours dutifully collecting data, but it felt as though new data was needed every week. It all started when someone decided to add another layer of tape to each boundary. The reasoning made sense: “It’ll be easier to read the color boundaries with more layers of tape because the colors *pop* more.” However, it was difficult to see that as fair when it meant we had to start from scratch.

It did lead to some good, in a roundabout way. After the second layer of green tape was added, our sensor simply could not distinguish red from orange or the gray mat from green. We were a wreck. It was here that Roger realized we didn’t only have the R, G, and B values at our disposal, but also the lux, which can be calculated using a function built into the RGB sensor’s library. Our readings were much more stable, but we struggled in the most important environment of all: the Villard room. (**dun dun DUNNNN**)

The Villard room is tricky. The lighting is constantly shifting because, unlike the lab, it has huge windows letting in sunlight of various intensity. Some of the other groups didn’t seem to struggle with this as much; we’re curious to read about their strategy and peer into the code. We did make one *huge* blunder, though: we didn’t separate our RGB data into two categories! Instead of saving the Villard room RGB values, we just recalibrated every single time from scratch. Let’s chalk that one up to sleep deprivation.

[Here’s a video showing how close we got to 3+ points in a round (solo or 1v1).](https://vimeo.com/218252159) The only reason it isn’t a victory is due to 2 slight interferences: Esther moving another robot out of the way and Esther feeding the egg down the sort servo when it got stuck(more on that in the next journal!). We could reasonably forgive the first one if we’re going for the solo round milestone, and all we needed to do for the second interference was program a break to ensure that our sort servo wouldn’t run endlessly in the event of a misread egg. Unfortunately, this was our last test run before our disastrous performance in the competition. So close! 

### Acknowledgments:
**Esther** designed the body and the sorting mechanism. **Roger** gathered RGB data for the boundary-searching RGBs and the egg-sorting RGB. **Tyler** wrote the eggSearch and boundarySearch algorithms. 
