## Project
- This is an implementation of a couple useful helper functions for OpenGL. This project takes inspiration from THREE.js found at https://threejs.org/
- uses libraries from 
- GLAD: https://glad.dav1d.de/
- glfw3: https://www.glfw.org/

## Windows Compilation
- For compilation on windows I used chocolatey to get make, gcc, and g++ on my system to compile all this from the command line / git bash.

- chocolatey can be found here: https://chocolatey.org/


## OpenGL 
- While i dislike column major arrays it's the opengl standard so all math operations in this project use column major systems to do matrix operations.


## Mesh Class
- The mesh will contain 3 pre defined attributes always available that it will bind to the shader if they are present, pos, normal, tangent

### TODO
- Look into quaternions and how to represent them in a graphics context


### BUGS
- scene Object causes program to not create cube on screen so debug sceneObject seems to be the mesh creating buffers most likely
- For now recompliling the math lib does not recompile all the changes in the actaul objects it must be done by doing make clean and make