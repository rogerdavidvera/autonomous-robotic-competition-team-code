# Milestone 5

## Detect an egg in another quadrant

This week's milestone was a simpler version of the previous milestone, and gave us a chance to recuperate. Our sensors and motors were struggling to work together, but Roger discovered this was due to the Pixy cam and IR sensor using the same pin. We disconnected the IR sensor for the time being and we were back in business! Our robot could finally move and detect objects.

In order to accomplish this milestone, we created a strategy:
1. Move into the quadrant directly across from our home quadrant
2. Turn left
3. Search for eggs
4. Repeat steps 2 & 3 until the egg in the quadrant is found
5. Determine the color of the egg and display that in a blinking LED

![Pixy cam finding egg](http://i38.photobucket.com/albums/e114/tykugler/Image-1_zpsczu6k5ul.jpg)

We know that approaching an egg will be difficult, so our robot isn't trying to do that right now. It only needs to display the color of the egg. Roger did the brunt of the work on this milestone. He edited Tyler's existing code to work for this milestone. He also measured the RGB values of the boundaries for future use; Roger and Tyler converted these hexadecimal values to separate decimal values so that the robot will be able to determine the boundary in later milestones. 

![Robot detecting boundaries](http://i38.photobucket.com/albums/e114/tykugler/Image-1%201_zpsatkuugsh.jpg)

Esther spent the week creating our morphology. She put in a lot of thought and work to create achievable ideas, since we now realize our original ideas may have been a bit too ambitious. Esther's work this week will bring us toward our final design for our robot. 

### Acknowledgments
**Esther** spent the week designing a future iteration of Ovi, our robot. **Tyler** and **Roger** wrote the code for egg detection and collected RGB values from a sensor for future use in boundary detection.
