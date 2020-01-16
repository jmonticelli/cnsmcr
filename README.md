# cnsmcr

**cnsmcr** (**c**o**ns**u**m**e **c**o**r**e) is a program that has only one goal:

Consume a requested amount of your CPU cycles on an arbitrary processor core.

This is done simply by doing some busy work, and sleeping for whatever portion of a fraction of a second remains (if there is any remainder of CPU usage specified by the user)

Build by simply running `make` and run the built executable `sudo nice --1 ./cnsmcr <0.1 - 100.0>`


### Q. Why would I want to consume a CPU core?
A. To provide the hottest way to handicap your CPU to emulate less-powerful hardware. Or, actually simulate resource strain in a reliable, and quantizable way.

### Q. Aren't there better ways?
A. I'm sure there are. But this is cheap (maybe not on your power bill, but), easy, and reliable. There are instances where you would *prefer* this over, say, cpulimit, like in cases where you are launching processes in repeat, one after the other, in a manner that is difficult to automate. A coworker had suggested a terrific alternative, which is underclocking. But still, that is something that will typically require at least a reboot to do, and another to undo.

### Q. Why doesn't it report my jennies?
A. Printing at all during this more or less breaks the accuracy of the target CPU consumption and makes it harder to track this process being run, as the process may hop across multiple CPUs while it awaits the blocking call to print to the screen to return. This could, however, be printed at the end when the application is killed. (tldr I'm lazy)

### Q. Why is this actually not taking up all of my CPU on one core (or the specified amount)?
A. Probably because you have not appropriately niced this process. This process is intended to be run with the highest priority (-20).
