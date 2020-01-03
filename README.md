# cnsmcr

**cnsmcr** (**c**on**s**u**m**e **c**o**r**e) is a program that has only one goal:

Consume a requested amount of your CPU cycles on an arbitrary processor core.

This is done simply by doing some busy work, and sleeping for whatever portion of a fraction of a second remains (if there is any remainder of CPU usage specified by the user)

Build by simply running `make` and run the built executable `sudo nice --20 ./cnsmcr <0.1 - 100.0>`


### Q. Why would I want to consume a CPU core?
A. To provide the hottest way to handicap your CPU to emulate less-powerful hardware.

### Q. Aren't there better ways?
A. I'm sure there are. But this is cheap, easy, and reliable.

### Q. Why doesn't it report my jennies?
A. Printing at all during this more or less breaks the accuracy of the target CPU consumption and makes it harder to track this process being run, as the process may hop across multiple CPUs while it awaits the blocking call to print to the screen to return. This could, however, be printed at the end when the application is killed. (tldr I'm lazy)

### Q. Why is this actually not taking up all of my CPU on one core (or the specified amount)?
A. Probably because you have not appropriately niced this process. This process is intended to be run with the highest priority (-20).
