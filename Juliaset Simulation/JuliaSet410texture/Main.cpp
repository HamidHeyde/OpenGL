/*-----------------------------------------------------------------------------
*                                  Headers
*-----------------------------------------------------------------------------*/
#include "Header.h"

#include "ModelJuliaSet.h"
#include "ModelTexture.h"
//Texture
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/*-----------------------------------------------------------------------------
*                             Global Variables
*-----------------------------------------------------------------------------*/
int WinWidth = 600; int WinHeight = 600;
int WinPosx = 100; int WinPosy = 10;

char* title = (char*)("Animated Julia Set");
char* path = (char*)"wall.jpg";

char *Tvpath = (char *)"Tvertex.vs";
char *Tfpath = (char *)"Tfrag.fs";
char *vpath = (char *)"vertex.vs";
char *fpath = (char *)"frag.fs";

ModelTexture *square;
ModelJuliaSet *triangle;

float step = 0;
bool is_animated = true;



/*-----------------------------------------------------------------------------
*                          Other Functions Declaration
*-----------------------------------------------------------------------------*/
int GlewCheckInit();

/*-----------------------------------------------------------------------------
*                        OPENGL Function Definition
*-----------------------------------------------------------------------------*/

void Timer(int value)
{
	if (is_animated)
	{
		step += 0.1;
		triangle->SetTimer(step);

		glutPostRedisplay();

		glutTimerFunc(10, Timer, 0);
	}
}

void init(void)
{
	glEnable(GL_DEPTH_TEST);

	//Create Models
	triangle = new ModelJuliaSet(vpath, fpath);
	square = new ModelTexture(Tvpath, Tfpath, path);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//------------------------------------------
	triangle->DrawModel(glm::vec3(0.f, 0.f, 0.f),0.f, glm::vec3(0, 0, 1),glm::vec3(1.f, 1.f, 1.f));
	square->DrawModel(glm::vec3(-1.4f, -1.4f, 0.f), 0.f, glm::vec3(0, 1, 0), glm::vec3(0.5f, 0.5f, 0.5f));
	//------------------------------------------

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	{
		exit(0);
		break;
	}
	case 32:
	{
		if (is_animated)
		{
			is_animated = false;
		}
		else
		{
			is_animated = true;
			Timer(0);
		}
		break;
	}
	}
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		step += 0.1;
		triangle->SetTimer(step);
		
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_DOWN:
	{
		step -= 0.1;
		triangle->SetTimer(step);

		glutPostRedisplay();
		break;
	}

	}
}

void MouseClick(int Key, int state, int x, int y)
{
}

void MouseMove(int x, int y)
{
}

void resize(int w, int h)
{
}


/*-----------------------------------------------------------------------------
*                                  Main
*-----------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	//For supporting GLSL 4.1
	glutInitContextVersion(4, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//--------------------------------------------------

	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(WinPosx, WinPosy);
	glutCreateWindow(title);
	//--------------------------------------------------

	//GLEW
	if (GlewCheckInit() == 1){ return 1; }
	//--------------------------------------------------

	//OPENGL Functions
	init();
	//glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);

	Timer(0);
	//glutIdleFunc(redraw);
	//--------------------------------------------------


	//Entering The Main Loop
	glutMainLoop();
	//--------------------------------------------------
	return 0;
}

/*-----------------------------------------------------------------------------
*                         Other Functions Definition
*-----------------------------------------------------------------------------*/

int GlewCheckInit()
{
	//GLEW Initialization
	glewInit();

	//Setting GLEW experimental to true
	glewExperimental = true;

	//Geting GLEW errors if there are any
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK){
		cout << "glew init error\n%s\n" << glewGetErrorString(glewError);
	}

	//Get OpenGL Version String and GLSL Version
	const GLubyte * p = glGetString(GL_VERSION);
	cout << "Graphics Driver: " << p << endl;

	const GLubyte * q = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << "GLSL Version: " << q << endl;

	return 0;
}