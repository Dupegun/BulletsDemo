# BulletsDemo

Multithreading simulation of bullets movement and collision in two-dimensional space using C++ and SFML.
-------------

[Download executable](https://mega.nz/file/sIJFgSJT#FRVsRH87phC-rLpM7xvoaz0Z-rVlpqQb0TNAXfx3aYI) You can use RunBulletsDemo.bat, or run directly  from "./Binaries/BulletsDemo/BulletsDemo.exe". **Use spacebar to launch a random bullet**

This is my solution for problem described below.

>Problem description:
A list of segments (walls), represented by two points on a plane, is predefined.
Your task is to write BulletManager class with two public methods:
* void Update (float time), where time – global update time in seconds. This method
calculates bullet movement in given time, and in case of collision with the wall, removes
the wall from the list and bullet continues movement with its trajectory reflected.
* void Fire (float2 pos, float2 dir, float speed, float time, float life_time), where pos –
starting point of the bullet on the plane (in meters), dir – direction, speed – bullet speed
(m/s), time – when the bullet will be fired, life_time – time before bullet disappears.
This method adds bullet to manager for further updates. Update method must be called
from main thread, but Fire method should be called from different threads.

>Other requirements:
* Your application should use all available core/treads of your CPU.
* You have to create visualization for this process. Render libraries can be used.
* Language required – C++.
* Write clean and readable code
* Implement the system with the appropriate data structures. High level libraries such as
STL or Boost can be used.
* Optimize your code.
* Comment the code to the degree that you feel is necessary.

**20K Bullets, click to open youtube**
[![20K Bullets](http://img.youtube.com/vi/undkD-UL0Ls/0.jpg)](https://www.youtube.com/watch?v=undkD-UL0Ls "20K Bullets")
