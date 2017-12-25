/*-----------------------------------------------------------------------------
*                                  Headers
*-----------------------------------------------------------------------------*/
#include "Header.h"
#include "LSytem.h"
#include "ModelTexture.h"

/*-----------------------------------------------------------------------------
*                             Global Variables
*-----------------------------------------------------------------------------*/
int WinWidth = 600; int WinHeight = 600;
int WinPosx = 100; int WinPosy = 10;
char* title = (char*)("LSystem Test 1");
char *vpath = (char *)"vertex.vs";
char *fpath = (char *)"frag.fs";

char *Tvpath = (char *)"Tvertex.vs";
char *Tfpath = (char *)"Tfrag.fs";
char* path = (char*)"g2.jpg";


float rd = 0;
int type;

float a, d, n, t;

char *First, *R1, *R2, *R3, *R4, *R5; 
float ANGLE, ITERATION, TYPE;
float DISTANCE = 0.3;

glm::vec4 c1, c2, c3;
bool threed = false;
bool forest = false;


glm::vec3 cameraPos = glm::vec3(0.0f, 35.0f, 80.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float pitch = 0.f;
float yaw = -90.f;
float cameraSpeed = 0.5;

int oldx = 0;
int oldy = 0; 
int offsetx = 0;
int offsety = 0;
bool ishold = false;

float formula[6];
/*----------------------------Variables---------------------------------*/

LSystemModel *Model;
LSystemModel *m[6];
ModelTexture *square;

/*-----------------------------------------------------------------------------
*                           Function Declaration
*-----------------------------------------------------------------------------*/
int GlewCheckInit();

/*-----------------------------------------------------------------------------
*                        OPENGL Function Definition
*-----------------------------------------------------------------------------*/

void calculateRotations()
{
	if (pitch > 89.f){ pitch = 89.f; }
	if (pitch < -89.f){ pitch = -89.f; }

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

void redraw()
{

}

void setformula(float n)
{
	switch ( (int) n)
	{
		case 1:
		{
			First = "F+F+F+F";
			R1 = "F+F-F-FF+F+F-F";
			R2 = "F";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("90");
			ITERATION = atof("4");
			TYPE = atof("0");
			break;
		}
		case 2:
		{
			First = "F+F+F+F";
			R1 = "FF+F+F+F+FF";
			R2 = "F";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("90");
			ITERATION = atof("4");
			TYPE = atof("0");
			break;
		}
		case 3:
		{
			First = "F+F+F+F";
			R1 = "FF+F+F+F+F+F-F";
			R2 = "F";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("90");
			ITERATION = atof("4");
			TYPE = atof("0");
			break;
		}
		case 4:
		{
			First = "L";
			R1 = "+RF-LFL-FR+";
			R2 = "-LF+RFR+FL-";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("90");
			ITERATION = atof("7");
			TYPE = atof("1");
			break;
		}
		case 5:
		{
			First = "L";
			R1 = "LFRFL+F+RFLFR-F-LFRFL";
			R2 = "RFLFR-F-LFRFL+F+RFLFR";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("90");
			ITERATION = atof("5");
			TYPE = atof("1");
			break;
		}
		case 6:
		{
			First = "L";
			R1 = "L+RF+";
			R2 = "-FL-R";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("90");
			ITERATION = atof("14");
			TYPE = atof("1");
			break;
		}
		case 7:
		{
			First = "R";
			R1 = "R+L+R";
			R2 = "L-R-L";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("60");
			ITERATION = atof("7");
			TYPE = atof("2");
			break;
		}
		case 8:
		{
			First = "R";
			R1 = "L+R++R-L--LL-R+";
			R2 = "-L+RR++R+L--L-R";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("60");
			ITERATION = atof("5");
			TYPE = atof("2");
			break;
		}
		case 9:
		{
			First = "F";
			R1 = "F[+F]F[-F]F";
			R2 = "F";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("25.7");
			ITERATION = atof("5");
			TYPE = atof("0");
			break;
		}
		case 10:
		{
			First = "X";
			R1 = "F[+X]F[-X]+X";
			R2 = "FF";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("20.7");
			ITERATION = atof("7");
			TYPE = atof("3");
			break;
		}
		case 11:
		{
			First = "X";
			R1 = "F-[[X]+X]+F[+FX]-X";
			R2 = "FF";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("22.5");
			ITERATION = atof("5");
			TYPE = atof("3");
			break;
		}
		case 12:
		{
			First = "X";
			R1 = "F[+X][-X]FX";
			R2 = "FF";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("25.7");
			ITERATION = atof("7");
			TYPE = atof("3");
			break;
		}
		case 13:
		{
			First = "F";
			R1 = "FF+[+F-F-F]-[-F+F+F]";
			R2 = "F";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("22.5");
			ITERATION = atof("4");
			TYPE = atof("4");
			break;
		}
		case 14:
		{
			First = "GFX[+G][-G]";
			R1 = "GFX[+G][-G]";
			R2 = "X[-FFF][+FFF]FX";
			R3 = "F";
			R4 = "F";
			R5 = "F";
			ANGLE = atof("25.7");
			ITERATION = atof("5");
			TYPE = atof("6");
			break;
		}
		case 15:
		{
			First = "SLFFF";
			R1 = "[+++G][---G]TS";
			R2 = "+H[-G]L";
			R3 = "-G[+H]L";
			R4 = "TL";
			R5 = "[-FFF][+FFF]F";
			ANGLE = atof("18");
			ITERATION = atof("9");
			TYPE = atof("7");
			break;
		}
		case 16:
		{
			First = "T";
			R1 = "R+[T]--[--L]R[++L]-[T]++T";
			R2 = "F[--L][++L]F";
			R3 = "[{+Q-Q-Q+@Q-Q-Q}]";
			R4 = "Q";
			R5 = "FF";
			ANGLE = atof("30");
			ITERATION = atof("5");
			TYPE = atof("8");
			break;
		}
	}
}

void init(void)
{
	glEnable(GL_DEPTH_TEST);

	//setformula(16);

	/*
	
	formula[0] = atof("11");
	formula[1] = atof("10");
	formula[2] = atof("9");
	formula[3] = atof("16");
	formula[4] = atof("14");
	formula[5] = atof("13");

	setformula(formula[0]); 
	

	c1 = glm::vec4(1.0, 0.0, 1.0, 1.0);
	c2 = glm::vec4(1.0, 1.0, 0.0, 1.0);
	c3 = glm::vec4(0.0, 1.0, 1.0, 1.0);

	threed = true;
	forest = false;
	
	*/

	if ((!forest))
	{
		cameraPos = glm::vec3(0.0f, 10.0f, 40.0f);
	}

	square = new ModelTexture(Tvpath, Tfpath, path);

	Model = new LSystemModel(vpath, fpath,
		First, R1, R2, R3, R4, R5,
		ANGLE, DISTANCE, ITERATION, TYPE,
		c1, c2, c3);
	
	m[0] = Model;
	
	if (formula[1] != 0)
	{
		setformula(formula[1]);
		
		m[1] = new LSystemModel(vpath, fpath,
			First, R1, R2, R3, R4, R5,
			ANGLE, DISTANCE, ITERATION, TYPE,
			c1, c2, c3);
	}
	if (formula[2] != 0)
	{
		setformula(formula[2]);

		m[2] = new LSystemModel(vpath, fpath,
			First, R1, R2, R3, R4, R5,
			ANGLE, DISTANCE, ITERATION, TYPE,
			c1, c2, c3);
	}
	if (formula[3] != 0)
	{
		setformula(formula[3]);

		m[3] = new LSystemModel(vpath, fpath,
			First, R1, R2, R3, R4, R5,
			ANGLE, DISTANCE, ITERATION, TYPE,
			c1, c2, c3);
	}
	if (formula[4] != 0)
	{
		setformula(formula[4]);

		m[4] = new LSystemModel(vpath, fpath,
			First, R1, R2, R3, R4, R5,
			ANGLE, DISTANCE, ITERATION, TYPE,
			c1, c2, c3);
	}
	if (formula[5] != 0)
	{
		setformula(formula[5]);

		m[5] = new LSystemModel(vpath, fpath,
			First, R1, R2, R3, R4, R5,
			ANGLE, DISTANCE, ITERATION, TYPE,
			c1, c2, c3);
	}
}

void Render3dtree(glm::vec3 pos, int mnum)
{

	m[mnum]->Camera(cameraPos,
		cameraPos + cameraFront, 
		cameraUp);

	for (int i = 0; i < 16; i++)
	{
		m[mnum]->DrawModel(pos,
			(i * 22.5), glm::vec3(0, 1, 0),
			glm::vec3(1.f, 1.f, 1.f));
	}

	
}

void Renderground(glm::vec3 size)
{
	square->Camera(cameraPos, 
		cameraPos + cameraFront, 
		cameraUp);

	square->DrawModel(glm::vec3(0.f, 0.f, 0.f),
		glm::radians(90.f), glm::vec3(1, 0, 0), 
		size);

}


void display(void)
{

	//For ZBuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (forest)
	{
		//-----ground

		Renderground(glm::vec3(100.f, 100.f, 1.f));

		//-------trees
		/*setformula(formula[0]);
		Render3dtree(glm::vec3(0.f, 0.f, 0.f),0);*/

		if (formula[1] == 0){ setformula(formula[0]); Render3dtree(glm::vec3(40.f, 0.f, 0.f), 0); }
		else { setformula(formula[1]); Render3dtree(glm::vec3(40.f, 0.f, 0.f), 1); }

		//****
		if (formula[2] == 0){ setformula(formula[0]); Render3dtree(glm::vec3(-40.f, 0.f, 0.f), 0); }
		else { setformula(formula[2]); Render3dtree(glm::vec3(-40.f, 0.f, 0.f), 2); }
		
		//-------------------------------------
		if (formula[3] == 0){ setformula(formula[0]); Render3dtree(glm::vec3(-20.f, 0.f, -40.f), 0); }
		else { setformula(formula[3]); Render3dtree(glm::vec3(-20.f, 0.f, -40.f), 3); }
		

		if (formula[4] == 0){ setformula(formula[0]); Render3dtree(glm::vec3(20.f, 0.f, -40.f), 0); }
		else { setformula(formula[4]); Render3dtree(glm::vec3(20.f, 0.f, -40.f), 4); }
		
		//-------------------------------------
		if (formula[5] == 0){ setformula(formula[0]); Render3dtree(glm::vec3(-20.f, 0.f, 40.f), 0); }
		else{ setformula(formula[5]); Render3dtree(glm::vec3(-20.f, 0.f, 40.f), 5); }
		

		setformula(formula[0]);
		Render3dtree(glm::vec3(20.f, 0.f, 40.f),0);
		//-------------------------------------
	}
	else if (threed)
	{
		Renderground(glm::vec3(35.f, 35.f, 1.f));
		Render3dtree(glm::vec3(0.f, 0.f, 0.f),0);
	}
	else
	{
		if (formula[0] > 8)
		{
			Renderground(glm::vec3(20.f, 20.f, 1.f));
		}
		

		Model->Camera(cameraPos, cameraPos + cameraFront, cameraUp);

		Model->DrawModel(glm::vec3(0.f, 0.f, 0.f),
			rd, glm::vec3(0, 0, 1),
			glm::vec3(1.f, 1.f, 1.f));
	}


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
	case 'd':
	{

		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		glutPostRedisplay();
		break;
	}
	case 'a':
	{

		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		glutPostRedisplay();
		break;
	}
	case 'w':
	{
		cameraPos +=  cameraSpeed * cameraUp;

		glutPostRedisplay();
		break;
	}
	case 's':
	{
		cameraPos -= cameraSpeed * cameraUp;

		glutPostRedisplay();
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
			cameraPos += cameraSpeed * cameraFront;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_DOWN:
		{
			cameraPos -= cameraSpeed * cameraFront;
			glutPostRedisplay();
			break;
		}
	}
}

void scroll(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		cameraPos += 2*cameraSpeed * cameraFront;
	}
	else
	{
		cameraPos -= 2*cameraSpeed * cameraFront;
	}

	glutPostRedisplay();
}

void MouseClick(int Key, int state, int x, int y)
{
	if (Key == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			oldx = x;
			oldy = y;

			ishold = true;
		}
		else if (state == GLUT_UP)
		{
			ishold = false;
		}
	}
	
}

void MouseMove(int x, int y)
{
	if (ishold)
	{
		offsetx = x - oldx;
		offsety = y - oldy;

		oldx = x;
		oldy = y;

		yaw += offsetx * (0.05);
		pitch += offsety * (0.05);

		calculateRotations();
		glutPostRedisplay();
	}
}

void resize(int w, int h)
{
}


/*-----------------------------------------------------------------------------
*                                  Main
*-----------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
	
	///*
	formula[0] = atof(argv[1]);
	formula[1] = atof(argv[2]);
	formula[2] = atof(argv[3]);
	formula[3] = atof(argv[4]);
	formula[4] = atof(argv[5]);
	formula[5] = atof(argv[6]);
	setformula(formula[0]); 
	//*/

	/*First = argv[1];
	R1 = argv[2];
	R2 = argv[3];
	R3 = argv[4];
	R4 = argv[5];
	R5 = argv[6];*/

	///*
	ANGLE = atof(argv[7]);
	ITERATION = atof(argv[8]);
	TYPE = atof(argv[9]);
	
	c1 = glm::vec4(atof(argv[10]), atof(argv[11]), atof(argv[12]), 1.0);
	c2 = glm::vec4(atof(argv[13]), atof(argv[14]), atof(argv[15]), 1.0);
	c3 = glm::vec4(atof(argv[16]), atof(argv[17]), atof(argv[18]), 1.0);
	
	if (atof(argv[19]) == 1) { threed = true; }
	else { threed = false; }
	//*/

	
	///*
	if (atof(argv[20]) == 1) { forest = true; }
	else { forest = false; }
	//*/

	/*
	//should be changed for texture
	if (atof(argv[21]) == 1) { forest = true; }
	else { forest = false; }
	*/
	


	glutInit(&argc, argv);

	//For ZBuffer, For animation its DOUBLE
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	//--------------------------------------------------

	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(WinPosx, WinPosy);
	glutCreateWindow(title);
	//--------------------------------------------------

	//Check GLEW availability
	if (GlewCheckInit() == 1){ return 1; }
	//--------------------------------------------------

	//OPENGL Functions
	init();
	//glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutMouseWheelFunc(scroll);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	//glutIdleFunc(redraw);
	//--------------------------------------------------


	//Entering The Main Loop
	glutMainLoop();
	//--------------------------------------------------
	return 0;
}

/*-----------------------------------------------------------------------------
*                           Function Definition
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

	//2. Get OpenGL Version String and GLSL Version string
	const GLubyte * p = glGetString(GL_VERSION);
	cout << "Graphics Driver: " << p << endl;

	const GLubyte * q = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << "GLSL Version: " << q << endl;

	//Checking specific GLEW Version
	if (!GLEW_VERSION_2_0)
	{
		cout << "OpenGL 2.0 Not Available" << endl;
		return 1;
	}

	return 0;
}