//
//  LSytem.h
//  OpenGLExercises


#ifndef LSytem_h
#define LSytem_h

/*----------------------------Header---------------------------------------*/
#include <math.h>
#include "ShaderOperation.h"
//GLM-----------------------------------------------------
#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/*----------------------------Class---------------------------------------*/
class LSystemModel
{

public:
    
    //Helpers
    void char2vec(char* s, vector<char> &v);
    void getNewDirection(char operation,glm::vec3 &direction);
    
    //constructor
    LSystemModel(char *vpath, char *fpath,
                 char* f,
                 char* r1,char* r2,char* r3,char* r4, char* r5,
                 float ang, float dis, int it, int t,
				 glm::vec4 col1, glm::vec4 col2, glm::vec4 col3);

    //Basic Setup
    void LinkVariables();
    void SetView(glm::mat4 vs);
    void SetProjection(glm::mat4 ps);
	void Camera(glm::vec3 x, glm::vec3 y, glm::vec3 z);
    
    
    
    //LSystem
    void SetupModel();
    void getFinalSentence();
    void getFinalSentence1();
    void getFinalSentence2();
    void getFinalSentence3();
    void getFinalSentence4();
    void getFinalSentence5();
    void getFinalSentence6();
    void getFinalSentence7();
    void getFinalSentence8();
    
    //GPU For Drawing The Model
    void InitObject();
    void DrawModel(glm::vec3 tv,
                   float rd, glm::vec3 rv,
                   glm::vec3 sr);
private:
    
    Shader *shader;
    GLuint arrID;
    GLuint PositionID;
    GLuint ColorID;
    GLuint ModelID;
    GLuint ViewID, ProjectionID;
    
    
    struct Vertex{
        glm::vec2 position;
        glm::vec4 color;
    };
    
    vector<Vertex> vertices;
    vector<GLuint> indices;
    
    vector<char> Sentence;
    vector<char> temp;

    
    vector<char> R1;
    vector<char> R2;
    vector<char> R3;
    vector<char> R4;
    vector<char> R5;
    
    
    vector<glm::vec3> stack;
    vector<glm::vec3> stackDir;
    
    float angle;
    float distance;
    int iteration;
    int type;

	glm::vec4 col[3];

	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
    
    
};
/*----------------------------Functions---------------------------------------*/

//Helpers
//--------------------------------------------------------------------------------

void LSystemModel::getNewDirection(char operation,glm::vec3 &direction)
{
    glm::mat3 t = glm::mat3(0.0);
    
    
    switch (operation) {
        case '-':
        {
            t[0][0] = glm::cos(-angle);     t[0][1] = -glm::sin(-angle);        t[0][2] = 0.f;
            
            t[1][0] = glm::sin(-angle);     t[1][1] = glm::cos(-angle);         t[1][2] = 0.f;
            
            t[2][0] = 0.f;                  t[2][1] = 0.f;                      t[2][2] = 0.f;
            
            break;
        }
        case '+':
        {
            t[0][0] = glm::cos(angle);      t[0][1] = -glm::sin(angle);         t[0][2] = 0.f;
            
            t[1][0] = glm::sin(angle);      t[1][1] = glm::cos(angle);          t[1][2] = 0.f;
            
            t[2][0] = 0.f;                  t[2][1] = 0.f;                      t[2][2] = 0.f;
            
            break;
        }
            
            
    }
    
    direction = t * direction;
}

void LSystemModel::char2vec(char* s, vector<char> &v)
{
    int i = 0;
    
    while(*(s+i)!= '\0')
    {
        v.push_back(*(s+i));
        i++;
    }
    
}

//Class Constructor
//--------------------------------------------------------------------------------
LSystemModel::LSystemModel(char *vpath, char *fpath,
                           char* f,
                           char* r1,char* r2,char* r3,char* r4, char* r5,
                           float ang, float dis, int it, int t,
						   glm::vec4 col1, glm::vec4 col2, glm::vec4 col3)
{
    //Program for Running the appication on GPU
    shader = new Shader(vpath,fpath);
    
    //Links Variables to Corresponding Fragment Variable
    LinkVariables();
    
    //Perspective
    SetProjection(glm::perspective( 3.14f / 2.0f, 1.f, 0.1f,-10.0f));
    
    
    //Intializing First Sentece, Rules and others
    
    char2vec (f,Sentence);
    
    char2vec (r1,R1);
    char2vec (r2,R2);
    char2vec (r3,R3);
    char2vec (r4,R4);
    char2vec (r5,R5);
    
    angle = glm::radians(ang);
    distance = dis;
    iteration = it;
    
    type=t;

	col[0] = col1;
	col[1] = col2;
	col[2] = col3;
    
    SetupModel();
}

//Basic Setup
//--------------------------------------------------------------------------------
void LSystemModel::LinkVariables()
{
    PositionID = glGetAttribLocation(shader->id(), "position");
    ColorID = glGetAttribLocation(shader->id(), "color");
    
    
    ModelID = glGetUniformLocation(shader->id(), "model");
    ViewID = glGetUniformLocation(shader->id(), "view");
    ProjectionID = glGetUniformLocation(shader->id(), "projection");
}
void LSystemModel::SetView(glm::mat4 vs)
{
    glUniformMatrix4fv( ViewID, 1, GL_FALSE, glm::value_ptr(vs) );
}
void LSystemModel::SetProjection(glm::mat4 ps)
{
    glUniformMatrix4fv( ProjectionID, 1, GL_FALSE, glm::value_ptr(ps) );
}
void LSystemModel::Camera(glm::vec3 x, glm::vec3 y, glm::vec3 z)
{
	eye = x;
	center = y;
	up = z;
}

//LSystem
//--------------------------------------------------------------------------------

void LSystemModel::getFinalSentence()
{
    
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if (temp.at(i)=='F')
            {
                for (int j=0;j<R1.size();j++)
                {
                    Sentence.push_back(R1.at(j));
                }
            }
            else
            {
                Sentence.push_back(temp.at(i));
            }
        }
    }
    
    //TESTING THE RESULT
   /* for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
    
}


 
void LSystemModel::getFinalSentence1()
{
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if (temp.at(i)=='L')
            {
                for (int j=0;j<R1.size();j++)
                {
                    Sentence.push_back(R1.at(j));
                }
            }
            else if (temp.at(i)=='R')
            {
                if (k>=1)
                {
                    for (int e=0;e<R2.size();e++)
                    {
                        Sentence.push_back(R2.at(e));
                    }
                }
            }
            else
            {
                Sentence.push_back(temp.at(i));
            }
        }
        
    }
    
    //TESTING THE RESULT
    /*for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
    
}


void LSystemModel::getFinalSentence2()
{
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if (temp.at(i)=='L')
            {
                for (int j=0;j<R1.size();j++)
                {
                    Sentence.push_back(R1.at(j));
                }
            }
            else if (temp.at(i)=='R')
            {
                for (int e=0;e<R2.size();e++)
                {
                    Sentence.push_back(R2.at(e));
                }
            }
            else
            {
                Sentence.push_back(temp.at(i));
            }
        }
        
    }
    
    temp.clear();
    temp = Sentence;
    Sentence.clear();
    
    for (int i=0; i<temp.size(); i++)
    {
        if (temp.at(i)=='L')
        {
            Sentence.push_back('X');
            Sentence.push_back('F');
        }
        else if (temp.at(i)=='R')
        {
            Sentence.push_back('Y');
            Sentence.push_back('F');
        }
        else
        {
            Sentence.push_back(temp.at(i));
        }
    }
    
    //TESTING THE RESULT
    /*for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
    
}

void LSystemModel::getFinalSentence3()
{
    
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if (temp.at(i)=='X')
            {
                for (int j=0;j<R1.size();j++)
                {
                    Sentence.push_back(R1.at(j));
                }
            }
            else if (temp.at(i)=='F')
            {
                for (int j=0;j<R2.size();j++)
                {
                    Sentence.push_back(R2.at(j));
                }
            }
            else
            {
                Sentence.push_back(temp.at(i));
            }
        }
        
    }
    
    //TESTING THE RESULT
   /* for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
    
}

void LSystemModel::getFinalSentence4()
{
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if (temp.at(i)=='F')
            {
                for (int j=0;j<R1.size();j++)
                {
                    Sentence.push_back(R1.at(j));
                }
            }
            else
            {
                Sentence.push_back(temp.at(i));
            }
        }
        
    }
    
    
    //TESTING THE RESULT
    /*for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
    
}


void LSystemModel::getFinalSentence5()
{
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if(i==(temp.size()-1))
            {
                if (temp.at(i)=='F')
                {
                    for (int e=0;e<R2.size();e++)
                    {
                        Sentence.push_back(R2.at(e));
                    }
                }
                else
                {
                    Sentence.push_back(temp.at(i));
                }
            }
            else
            {
                if ((temp.at(i)=='F')&&(temp.at(i+1)==']'))
                {
                    for (int j=0;j<R1.size();j++)
                    {
                        Sentence.push_back(R1.at(j));
                    }
                    
                    i++;
                    
                }
                else if (temp.at(i)=='F')
                {
                    for (int e=0;e<R2.size();e++)
                    {
                        Sentence.push_back(R2.at(e));
                    }
                }
                else
                {
                    Sentence.push_back(temp.at(i));
                }
            }
        }
        
    }
    
    
    //TESTING THE RESULT
   /* for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
    
}

void LSystemModel::getFinalSentence6()
{
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if (temp.at(i)=='G')
            {
                for (int j=0;j<R1.size();j++)
                {
                    Sentence.push_back(R1.at(j));
                }
            }
            else if (temp.at(i)=='X')
            {
                for (int r=0;r<R2.size();r++)
                {
                    Sentence.push_back(R2.at(r));
                }
            }
            else
            {
                Sentence.push_back(temp.at(i));
            }
        }
        
    }
    
    
    //TESTING THE RESULT
    /*for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
    
}

void LSystemModel::getFinalSentence7()
{
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if (temp.at(i)=='S')
            {
                for (int j=0;j<R1.size();j++)
                {
                    Sentence.push_back(R1.at(j));
                }
            }
            else if (temp.at(i)=='G')
            {
                for (int r=0;r<R2.size();r++)
                {
                    Sentence.push_back(R2.at(r));
                }
            }
            else if (temp.at(i)=='H')
            {
                for (int r=0;r<R3.size();r++)
                {
                    Sentence.push_back(R3.at(r));
                }
            }
            else if (temp.at(i)=='T')
            {
                for (int r=0;r<R4.size();r++)
                {
                    Sentence.push_back(R4.at(r));
                }
            }
            else if (temp.at(i)=='L')
            {
                for (int r=0;r<R5.size();r++)
                {
                    Sentence.push_back(R5.at(r));
                }
            }
            else
            {
                Sentence.push_back(temp.at(i));
            }
        }
        
    }
    
    
    //TESTING THE RESULT
    /*for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
    
}

void LSystemModel::getFinalSentence8()
{
    for (int k=0;k<iteration;k++)
    {
        temp.clear();
        temp = Sentence;
        Sentence.clear();
        
        for (int i=0; i<temp.size(); i++)
        {
            if (temp.at(i)=='T')
            {
                for (int j=0;j<R1.size();j++)
                {
                    Sentence.push_back(R1.at(j));
                }
            }
            else if (temp.at(i)=='R')
            {
                for (int r=0;r<R2.size();r++)
                {
                    Sentence.push_back(R2.at(r));
                }
            }
            else if (temp.at(i)=='L')
            {
                for (int r=0;r<R3.size();r++)
                {
                    Sentence.push_back(R3.at(r));
                }
            }
            else if (temp.at(i)=='F')
            {
                Sentence.push_back('F');
                Sentence.push_back('F');
            }
            else
            {
                Sentence.push_back(temp.at(i));
            }
        }
        
    }
    
    
    temp.clear();
    temp = Sentence;
    Sentence.clear();
    
    for (int i=0; i<temp.size(); i++)
    {
        if (temp.at(i)=='Q')
        {
            Sentence.push_back('F');
            Sentence.push_back('X');
            
        }
        else
        {
            Sentence.push_back(temp.at(i));
        }
        
    }
    
    //TESTING THE RESULT
    /*for (int p=0;p<Sentence.size(); p++)
    {
        cout<<Sentence.at(p);
    }
    
    cout<<endl;*/
}



void LSystemModel::SetupModel()
{
    //--------------------------
    vertices.clear();
    indices.clear();
    stack.clear();
    stackDir.clear();
    
    //--------------------------
    Vertex tempVertex;
    glm::vec4 white = glm::vec4 (1.0,1.0,1.0,1.0);
    glm::vec4 black = glm::vec4 (0.0,0.0,0.0,1.0);
	glm::vec4 green = glm::vec4 (0.56,0.69,0.40,1.0);

	/*glm::vec4 col[3] = {
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0)
	};*/

	/*col[0] = glm::vec4(1.0, 1.0, 1.0, 1.0);
	col[1] = glm::vec4(1.0, 1.0, 1.0, 1.0);
	col[2] = glm::vec4(1.0, 1.0, 1.0, 1.0);*/

    //--------------------------
    
    switch (type) {
        case 0:
            getFinalSentence();
            break;
        
        case 1:
            getFinalSentence1();
            break;
        
        case 2:
            getFinalSentence2();
            break;
        
        case 3:
            getFinalSentence3();
            break;
         
        case 4:
            getFinalSentence4();
            break;
            
        case 5:
            getFinalSentence5();
            break;
        
        case 6:
            getFinalSentence6();
            break;
            
        case 7:
            getFinalSentence7();
            break;
            
        case 8:
            getFinalSentence8();
            break;
            
            
    }
    
    
    //--------------------------
    
    glm::vec3 origin = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 dir = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 stepResult;
    
    //--------------------------
    
    
    stepResult = origin;
    tempVertex = {glm::vec2(stepResult.x,stepResult.y),white};
	//tempVertex = { glm::vec2(stepResult.x, stepResult.y), green };
    vertices.push_back(tempVertex);
    
    
    
    for (int i=0; i<Sentence.size();i++)
    {
        char current = Sentence.at(i);
        
        switch (current) {
            case 'F':
            {
                stepResult = (distance * dir)+ origin;

				//tempVertex = { glm::vec2(stepResult.x, stepResult.y), green };
				int index = rand() % 10;
				while (index > 2){ index -= 2; }
				tempVertex = { glm::vec2(stepResult.x, stepResult.y), col[index] };

                vertices.push_back(tempVertex);
                
                origin = stepResult;
                
                break;
            }
                
            case '+':
            {
                getNewDirection('+',dir);
                break;
            }
                
            case '-':
            {
                getNewDirection('-',dir);
                break;
            }
            case '@':
            {
                float oldAngle = angle;
                
                angle = 135.f;
                
                getNewDirection('-',dir);
                
                angle = oldAngle;
                
                break;
            }
            case '[':
            {
                stack.push_back(origin);
                stackDir.push_back(dir);
                
                break;
            }
            case ']':
            {
                if (stack.size()==0)
                {
                }
                else
                {
                    origin = stack.at(stack.size()-1);
                    dir = stackDir.at(stackDir.size()-1);
                    
                    tempVertex = {glm::vec2(origin.x,origin.y),black};
                    vertices.push_back(tempVertex);
                    
                    stack.pop_back();
                    stackDir.pop_back();
                }
                break;
            }
        }
    }
    
    
    
    //Filling the arrays
    InitObject();
    
}


//GPU for Drawing The Model
//--------------------------------------------------------------------------------

void LSystemModel::InitObject()
{
    GLuint bufferID;
    
    
    GENVERTEXARRAYS(1, &arrID);
    BINDVERTEXARRAY(arrID);
    
    //Create Bind BufferID
    glGenBuffers(1, &bufferID);
    glBindBuffer( GL_ARRAY_BUFFER, bufferID);
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW );
    
    
    glEnableVertexAttribArray(PositionID);
    glEnableVertexAttribArray(ColorID);
    
    //Sending Values to The GPU
    glVertexAttribPointer(PositionID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 );
    glVertexAttribPointer(ColorID, 4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)sizeof(glm::vec2) );
    
    
    //Unbind the buffers
    BINDVERTEXARRAY(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0);
    
    
}
void LSystemModel::DrawModel(glm::vec3 tv,
                              float rd, glm::vec3 rv,
                              glm::vec3 sr)
{
    //Bind Shader
    glUseProgram(shader->id());
    
    
    //Bind Vertex Array Object
    BINDVERTEXARRAY(arrID);
    
    //----------------------------------------------------
    
    //Set Model
    
    glm::mat4 t = glm::translate(glm::mat4(), tv);
    glm::mat4 r = glm::rotate(glm::mat4(), glm::radians(rd), rv );
    glm::mat4 s = glm::scale(glm::mat4(), sr);
    
    glm::mat4 model = t*r*s;
    
    glUniformMatrix4fv( ModelID, 1, GL_FALSE, glm::value_ptr(model));
    
    
    //----------------------------------------------------
    
	SetView(glm::lookAt(eye, center, up));
    
    //----------------------------------------------------
    
    //DRAW METHOD
    
    glDrawArrays(GL_LINE_STRIP, 0, (int)vertices.size());
    
    
    //Unbind Vertex Array Object and Shader
    BINDVERTEXARRAY(0);
    
    //UNBIND SHADER
    glUseProgram(0);
    
}

#endif /* LSytem_h */
