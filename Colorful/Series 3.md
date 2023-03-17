# Series 3

<img width="250" alt="截屏2023-03-17 14 03 28" src="https://user-images.githubusercontent.com/57748663/225977908-2adee9f8-629c-4765-a940-37e2341ea1bd.png">

## Video Link: https://youtu.be/yHdad2Sg2N8

Series 3 optimizes the center model based on the attempts of Series 2, using lines of random colors to create the effect that the central sphere disappears.

The program starts by loading a sound file and setting some initial parameters, such as the frame rate, window title, background color, line width, and depth test. It then generates an icosphere primitive with a radius of 250 and a level of 7, which is used to generate a list of random locations for the particle system.

In the update function, the particle system is updated by calling the update function of each particle in the vector. The program also generates a new set of particles by creating a log of points with a random color and lifespan, which is updated each frame based on noise values. The log of points is then drawn as a shape with a varying line width, which gives the appearance of a particle trail. Finally, a sphere is drawn in the center of the 3D space with a random color.

In the draw function, the particle system is drawn by looping through each particle in the vector and calling the draw function of each one. The log of points is also drawn as a shape with a varying line width, and the sphere is drawn in the center of the 3D space. The camera is then moved to the center of the 3D space and rotated around the Y-axis based on the current frame number.

The keyPressed function plays the sound file when the "p" key is pressed, and the mousePressed function sets a new random hue value for the particles when the mouse is clicked.

The particle class is defined at the end of the program and includes functions for updating and drawing each particle. The particles are drawn as a small rectangle with a color based on the hue value passed to the constructor.

Reference：https://junkiyoshi.com/

https://openframeworks.cc/learning/04_sound/play_a_sound/（sound）

https://pixabay.com/sound-effects/search/mp3/(sound)

https://www.color-hex.com/(hex color sheet)
