%%%Projects
===================================================================================
++Run WindowsApplication.exe in "FinalEXE" folder to see the final output and how everything works.

++Interface folder is the win-form application which interacts with the users and sends the parameters and commands to the Render which is a console-based application

++Renderer is the console-based application which is responsible for drawing all the trees on the screen using OpenGL - GLUT - C++

===================================================================================
%%%Description
===================================================================================

-Using L-System formula and the parameters, the renderer (OpenGL - C++ console-based application) renders 3D trees and bushes on screen. The user can also try different outputs by modifying the parameters (Iteration-Angle) and compare them together. The user can also choose to render a combination of these trees and bushes on a single ground. The Camera movement in all directions has been also implemented in the program.

-The user communicates with the Renderer through a Win-form application (C#) in which the one would be able to observe the parameters and formulas, change them and run the program.

Application:
Renderer (console-based): Opengl - C++ - GLUT
Interface (win-form): C# 
[These two programs communicate through Command-line]