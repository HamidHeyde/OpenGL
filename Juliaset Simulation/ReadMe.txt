%%%Output
===================================================================================
The output is an animated Julia Set (Timer-Based) and a Textured square (visible on the left-bottom corner)

By pressing "Space" key, the program pauses at the current state and by pressing "Space" key again, the program resumes the animation from the current state.

After pausing at the current state,(by pressing "Space" key), you can also use "Arrow Keys (Up and Down)" to move a step forward or backward and observe the changes manually. You can then resume the program from the current state by pressing "Space" key again.



%%%Program Structure
===================================================================================
* "stb_image.h" is the third-party library being used for Loading a JPG image (Wall.jpg) from file for the texturing the square.

===================================================================================

*"ShaderOperation.h" is responsible for loading 2 shaders (Vertex and Fragment) and creating a program using these shaders. It also compiles and links these shaders to the program and returns any possible ERROR.


*If everything works fine and there is no ERROR, it creates a specific ID for that program which will then be used for linking and binding purposes and finally drawing the model on the screen.
===================================================================================

*Files:

++"ModelJuliSet" which is responsible for all the Julia Set calculations and delivering the final output using those calculations.

++"ModelTexture" which is responsible for drawing a simple Square and binding a texture to that.
===================================================================================
