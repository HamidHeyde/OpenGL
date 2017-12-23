
#ifndef ModelJuliaSet_h
#define ModelJuliaSet_h

/*----------------------------Header---------------------------------------*/
#include <math.h>
#include "ShaderOperation.h"
//GLM-----------------------------------------------------
#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/*----------------------------Class---------------------------------------*/
class ModelJuliaSet
{
public:
    
	ModelJuliaSet(char *vpath, char *fpath);
    ModelJuliaSet(char *vpath, char *fpath, float t);
    glm::vec2 Square(glm::vec2 input);

    void LinkVariables();
	void SetTheScene();
    void SetView(glm::mat4 vs);
    void SetProjection(glm::mat4 ps);
 
    void SetupModel();
    void SetTimer(float t);
    void InitObject();
    void DrawModel( glm::vec3 tv,
                    float rd, glm::vec3 rv,
                    glm::vec3 sr);
private:
    Shader *shader;
    GLuint arrID;
    GLuint PositionID;
    GLuint ColorID;
    GLuint ModelID;
    GLuint ViewID, ProjectionID;
    float timer;
  
    
    struct Vertex{
        glm::vec2 position;
        glm::vec4 color;
    };
    
    vector<Vertex> vertices;
    vector<GLuint> indices;
    
};
/*----------------------------Functions---------------------------------------*/
void ModelJuliaSet::SetTimer(float t)
{
    timer = t;
	SetupModel();
    InitObject();
}

ModelJuliaSet::ModelJuliaSet(char *vpath, char *fpath)
{
	shader = new Shader(vpath, fpath);

	LinkVariables();

	SetTheScene();

	timer = 0;

	//SetupModel();
	SetupModel();
	InitObject();
}

ModelJuliaSet::ModelJuliaSet (char *vpath, char *fpath, float t)
{
    shader = new Shader(vpath,fpath);
    
    LinkVariables();
    
	SetTheScene();
    
    timer = t;
    
    //SetupModel();
	SetupModel();
    InitObject();
}

void ModelJuliaSet::SetTheScene()
{
	SetView(glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	SetProjection(glm::perspective(3.14f / 2.0f, 1.f, 0.1f, -10.0f));
	//SetProjection(glm::frustum(-1.f, 1.f, -1.f, 1.f, 1.f, 10.f));
}

void ModelJuliaSet::LinkVariables()
{
    PositionID = glGetAttribLocation(shader->id(), "position");
    ColorID = glGetAttribLocation(shader->id(), "color");
    
    
    ModelID = glGetUniformLocation(shader->id(), "model");
    ViewID = glGetUniformLocation(shader->id(), "view");
    ProjectionID = glGetUniformLocation(shader->id(), "projection");
}

void ModelJuliaSet::SetView(glm::mat4 vs)
{
    glUniformMatrix4fv( ViewID, 1, GL_FALSE, glm::value_ptr(vs) );
}

void ModelJuliaSet::SetProjection(glm::mat4 ps)
{
    glUniformMatrix4fv( ProjectionID, 1, GL_FALSE, glm::value_ptr(ps) );
}

glm::vec2 ModelJuliaSet::Square(glm::vec2 input)
{
    float w = 0.1*3.14;
    float x, y, rx, ry;
    
    x = input.x;
    y = input.y;
    
    rx = (x*x) - (y*y);
    //rx+=timer;
    rx+= 0.7885 * (cos (w*timer));
    
    ry = 2*x*y;
    ry+= sin(w*timer);
    
    
    return (glm::vec2(rx,ry));
}

void ModelJuliaSet::SetupModel()
{
	vertices.clear();
	indices.clear();

	glm::vec4 temp;

	glm::vec4 gray = glm::vec4(0.95, 0.95, 0.96, 1);
	glm::vec4 purple = glm::vec4(0.30, 0.14, 0.52, 1);
	glm::vec4 c1 = glm::vec4(1.0, 0.0, 0.52, 1);
	glm::vec4 c2 = glm::vec4(1.0, 0.1, 0.52, 1);
	glm::vec4 c3 = glm::vec4(1.0, 0.2, 0.52, 1);
	glm::vec4 c4 = glm::vec4(1.0, 0.3, 0.52, 1);
	glm::vec4 c5 = glm::vec4(1.0, 0.4, 0.52, 1);
	glm::vec4 c6 = glm::vec4(1.0, 0.5, 0.52, 1);
	glm::vec4 c7 = glm::vec4(1.0, 0.6, 0.52, 1);
	glm::vec4 c8 = glm::vec4(1.0, 0.7, 0.52, 1);
	glm::vec4 c9 = glm::vec4(1.0, 0.8, 0.52, 1);

	
	glm::vec2 point, result;


	for (float ii = -2; ii<2; ii += 0.01)
	{
		for (float jj = -2; jj<2; jj += 0.01)
		{
			point = glm::vec2(ii, jj);
			result = point;

			temp = purple;

			for (int i = 0; i<100; i++)
			{
				result = Square(result);

				if ((result.x > 1000) || (result.x < -1000))
				{
					if (i<1) { temp = c1; }
					else if (i<2) { temp = c2; }
					else if (i<3) { temp = c3; }
					else if (i<4) { temp = c4; }
					else if (i<5) { temp = c5; }
					else if (i<6) { temp = c6; }
					else if (i<7) { temp = c7; }
					else if (i<8) { temp = c8; }
					else if (i<9) { temp = c9; }
					else { temp = gray; }
					break;
				}
			}

			
			vertices.push_back({ point, temp });
		}
	}

	

	for (int j = 0; j< (int)vertices.size(); j++)
	{
		indices.push_back(j);
	}

}

void ModelJuliaSet::InitObject()
{
    GLuint bufferID;
    GLuint elementID;
    
    
    GENVERTEXARRAYS(1, &arrID);
    BINDVERTEXARRAY(arrID);
    
    //Create Bind BufferID
    glGenBuffers(1, &bufferID);
    glBindBuffer( GL_ARRAY_BUFFER, bufferID);
    //glBufferData( GL_ARRAY_BUFFER, 3 * sizeof(Vertex), triangle, GL_STATIC_DRAW );
    //glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW );
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    
    //glEnableVertexAttribArray(PositionID);
    //glEnableVertexAttribArray(ColorID);
    
    //Sending Values to The GPU
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 );
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)sizeof(glm::vec2) );
	glEnableVertexAttribArray(1);
    
    
    //ElementID
    glGenBuffers(1, &elementID);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, elementID);
    //glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW );
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    
    //Unbind the buffers
    BINDVERTEXARRAY(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
    
    
}

void ModelJuliaSet::DrawModel(glm::vec3 tv,
                      float rd, glm::vec3 rv,
                      glm::vec3 sr)
{
    //Bind Shader
    glUseProgram(shader->id());
    
    
    //Bind Vertex Array Object
    BINDVERTEXARRAY(arrID);
    
    //Set Model
    
    glm::mat4 t = glm::translate(glm::mat4(), tv);
    glm::mat4 r = glm::rotate(glm::mat4(), rd, rv );
    glm::mat4 s = glm::scale(glm::mat4(), sr);
    
    glm::mat4 model = t*r*s;
    glUniformMatrix4fv( ModelID, 1, GL_FALSE, glm::value_ptr(model));
    
    
    //DRAW METHOD
    glPointSize(2.f);
    glDrawArrays(GL_POINTS, 0, (int)indices.size());
    //glDrawElements(GL_LINE_STRIP, (int)indices.size(), GL_UNSIGNED_INT, 0);
    
    
    //Unbind Vertex Array Object and Shader
    BINDVERTEXARRAY(0);
    
    //UNBIND SHADER
    glUseProgram(0);
    
}


#endif /* Model_h */
