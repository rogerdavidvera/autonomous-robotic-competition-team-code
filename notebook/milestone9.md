# Milestone 9

## Move two eggs to increase your net score

Unfortunately, we weren’t able to pass this milestone. It should have been rather easy, but after passing milestone 8, we got a little confident. So let’s break it down.

For Ovi, grabbing 2 eggs is as easy as grabbing 1. Our robot hoards eggs, so as long as Ovi can return home, there shouldn’t be an issue. Of course, this is where we started to go wrong. Ovi finds eggs by moving in an arc to the left, going around the arena counterclockwise. This eggSearch method wasn’t really working for us; we knew it could work for the milestone, but we wanted to do well in the competition. 

So we made our arc larger, which causes more interactions with the white line. When Ovi hits a white line, it reverses, then spins a certain number of degrees. We ran out of time while testing our boundarySearch (more on that in the next journal!), and left our angle at 180 degrees. What follows is predictable and tragic: Ovi would grab our egg in quadrant B, hit a white line, spin to face our home quadrant (quadrant A), grab our egg in our home quadrant, then attempt to find home, when it would discover that it’s already home and stop. It grabbed two eggs, sure -- but one of them doesn’t count since it started in quadrant A. 

We couldn’t just collect more eggs (3 or 4 instead of 2) because our robot wouldn’t make it back in time. If we increased the speed of our robot, it stopped reading the white line accurately. If we missed the white line, there was NO shot of making it back home in time. 

[Here's a video showcasing how the angle Ovi turned to set us in the wrong direction, preventing us from grabbing 2 eggs from outside our original quadrant.](https://vimeo.com/218252405)

We’re confident that we could’ve gotten it to work. We just need a bit more time to tweak the angles, but 7am rolled around and we had to transport the mat to the Villard room to do RGB and pixy testing. It’s not like we could have put any more time into it: after each of us spent at least 6 all-nighters in the lab, at a certain point our work has to just speak for itself. Unfortunately, it was more of a whisper. 

Since we were unable to pass this milestone, the next two are also failures. Instead of saying the same thing every time, we’ve split things up so that one of our mistakes is presented in each journal. This entry: the angles of our turns. Next entry: that dreaded boundarySearch!

### Acknowledgments: 
**Esther** designed the body. **Tyler** wrote the algorithms for detecting, tracking, and stopping in front of eggs. **Roger** collected RGB data and configured the pixy camera for these algorithms.
