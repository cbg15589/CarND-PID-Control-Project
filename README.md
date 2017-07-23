# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program
---
## Introduction

After learning the basics of PID controllers in the lessons, in this project, we must build a C++ implementation of the PID controller.
The controller must then interact with the simulator via a websocket. The simulator provides current cross-track error, steering angle and speed, based on this inputs we must provide commands to both the steering and throttle.

## Reflection

- *Describe the effect each of the P, I, D components had in your implementation.*

The P (Proportional) component makes the car to steer to the lane center proportionally to the cross-track error. In absence of the other components, the car will oscillate over the lane center. The bigger the P component the bigger amplitude and shorter period of the oscillations.

The D (Differential) component steers the car based on the change of the cross-track error. This effectively damps the oscillations created by the P component.

The I (Integral) component steers the car based on the accumulated cross-track error. This counteracts the bias on the steering created by the vehicle itself or the curves on the track. For example, if we were driving on a constant radio circle, the output from the P component would be always 0 at the center of the lane, making the vehicle to drift apart from the center. Tuning the P and D components we could make the vehicle to follow the circle, but with a bigger radio. The I component is capable to counter this bias over time making the vehicle follow the center of the lane.
In this particular project, as I believe the vehicle doesn't have any bias on the steering, the I component helps us mainly on the curves, giving us the ability to follow them closer to the lane center.


- *Describe how the final hyperparameters were chosen.*

First I manually tuned the hyperparamaters until I could make continuous laps around the track. Then I added the throttle controller and re-tuned both controllers to make faster laps. Later, I was planning to automate the parameter optimization using twiddle as in the lessons but then I discarded the idea. The reason behind, is that when manually tuning, I couldn't get the setting that would work great on both curves and straights and I didn't think that Twiddle could give me the answer. Additionally, I think that evaluating the controller based only on the accumulated error is not a good idea. As a passenger I would prefer a smoother drive with more error than a controller that react too aggressively.

Below you can find some videos of the different values I tried

Better on straights (Kp = 0.06 Kd=3):

[Curve](https://www.youtube.com/watch?v=uBq4mfa7BrY)

[Straight](https://www.youtube.com/watch?v=x0gSxKwrPLQ)

Better on curves (Kp = 0.3 Kd=6):

[Curve](https://www.youtube.com/watch?v=ozFIv030Hjw)

[Straight](https://www.youtube.com/watch?v=UymN3d3U5fc)

The less aggressive settings have problems following the curves without leaving the track, and the more aggressive settings oscillate too much on the straights. I then thought about how could I combine both settings, an easy way I found is to update Kp and Kd based on the current angle. This way we will steer more aggressively on curves while maintaining a smooth driving on straights. 

the formulas I used are:

Kp = 0.06 + fabs(angle)*(0.3-0.06)/25

Kd = 3 + fabs(angle)*(6 - 3) / 25

Example of a full lap with the combined settings:

[Full Lap](https://www.youtube.com/watch?v=HyE_bX5rQjc)




---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
