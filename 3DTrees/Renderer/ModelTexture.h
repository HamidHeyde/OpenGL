#ifndef ModelTexture_h
#define ModelTexture_h

/*----------------------------Header---------------------------------------*/
#include <math.h>
#include "ShaderOperation.h"
//GLM-----------------------------------------------------
#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//Texture-----------------------------------------------------
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
/*----------------------------Class---------------------------------------*/

class ModelTexture
{
public:

	ModelTexture(char *vpath, char *fpath, char *ppath);

	void SetTexture(bool is_texture);
	void LinkVariables();
	void SetTheScene();
	void SetView(glm::mat4 vs);
	void SetProjection(glm::mat4 ps);

	void SetupModel();
	void InitObject();
	void InitTexture();

	void DrawModel(glm::vec3 tv,
		float rd, glm::vec3 rv,
		glm::vec3 sr);

	void Camera(glm::vec3 x, glm::vec3 y, glm::vec3 z);


private:
	Shader *shader;

	char *PicPath;

	GLuint tID;
	GLuint arrID;
	GLuint ModelID;
	GLuint ViewID, ProjectionID;
	GLuint is_textureID;
	


	struct Vertex{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texture;
	};

	vector<Vertex> vertices;
	vector<GLuint> indices;

};

glm::vec3 eye;
glm::vec3 center;
glm::vec3 up;


ModelTexture::ModelTexture(char *vpath, char *fpath, char *ppath)
{
	shader = new Shader(vpath, fpath);

	PicPath = ppath;

	LinkVariables();

	SetTheScene();

	SetupModel();
	InitObject();
	InitTexture();
}
void ModelTexture::Camera(glm::vec3 x, glm::vec3 y, glm::vec3 z)
{
	eye = x;
	center = y;
	up = z;
}
void ModelTexture::SetTexture(bool is_texture)
{
	float texture;
	if (is_texture)
	{
		texture = 1.0;
		glProgramUniform1f(shader->id(), is_textureID , texture);
	}
	else
	{
		texture = 0.0;
		glProgramUniform1f(shader->id(), is_textureID, texture);
	}

	SetupModel();
	InitObject();
	InitTexture();
}

void ModelTexture::LinkVariables()
{
	ModelID = glGetUniformLocation(shader->id(), "model");
	ViewID = glGetUniformLocation(shader->id(), "view");
	ProjectionID = glGetUniformLocation(shader->id(), "projection");

	is_textureID = glGetUniformLocation(shader->id(), "is_texture");
	float texture = 1.0;
	glProgramUniform1f(shader->id(), is_textureID, texture);

	GLuint SamplerID = glGetUniformLocation(shader->id(), "tex");
	glProgramUniform1i(shader->id(), SamplerID, 0);
}

void ModelTexture::SetTheScene()
{
	SetView(glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	SetProjection(glm::perspective(3.14f / 2.0f, 1.f, 0.1f, -10.0f));
	//SetProjection(glm::frustum(-1.f, 1.f, -1.f, 1.f, 1.f, 10.f));
}

void ModelTexture::SetView(glm::mat4 vs)
{
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, glm::value_ptr(vs));
}

void ModelTexture::SetProjection(glm::mat4 ps)
{
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, glm::value_ptr(ps));
}

void ModelTexture::SetupModel()
{
	vertices.clear();
	indices.clear();

	vertices.push_back({ { 0.5f, 0.5f, 0.5f }, { 1.f, 0.f, 0.f, 1.f }, { 1.0f, 1.0f } }); //0
	vertices.push_back({ { 0.5f, -0.5f, 0.5f }, { 0.f, 1.f, 0.f, 1.f }, { 0.0f, 1.0f } }); //1
	vertices.push_back({ { -0.5f, -0.5f, 0.5f }, { 0.f, 0.f, 1.f, 1.f }, { 0.0f, 0.0f } }); //2
	vertices.push_back({ { -0.5f, 0.5f, 0.5f }, { 1.f, 1.f, 1.f, 1.f }, { 1.0f, 0.0f } }); //3

	GLuint squareIndices[] = {
		0, 1, 2,
		2, 3, 0,
	};


	for (int j = 0; j < 6; j++)
	{
		indices.push_back(squareIndices[j]);
	}

}

void ModelTexture::InitObject()
{
	GLuint bufferID;
	GLuint elementID;


	GENVERTEXARRAYS(1, &arrID);
	BINDVERTEXARRAY(arrID);

	//Create Bind BufferID
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//glBufferData( GL_ARRAY_BUFFER, 3 * sizeof(Vertex), triangle, GL_STATIC_DRAW );
	//glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW );
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);


	//glEnableVertexAttribArray(PositionID);
	//glEnableVertexAttribArray(ColorID);

	//Sending Values to The GPU
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ((void*)(sizeof(glm::vec3) + sizeof(glm::vec4))));
	glEnableVertexAttribArray(2);


	//ElementID
	glGenBuffers(1, &elementID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
	//glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW );
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	//Unbind the buffers
	BINDVERTEXARRAY(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void ModelTexture::InitTexture()
{
	glGenTextures(1, &tID);
	glBindTexture(GL_TEXTURE_2D, tID);

	// set the texture wrapping/filtering options 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	// load and generate the texture
	int width, height, nrChannels;


	unsigned char *data = stbi_load(PicPath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void ModelTexture::DrawModel(glm::vec3 tv,
	float rd, glm::vec3 rv,
	glm::vec3 sr)
{
	//Bind Shader
	glUseProgram(shader->id());

	//Texture
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, tID);

	//Bind Vertex Array Object
	BINDVERTEXARRAY(arrID);

	//Set Model

	glm::mat4 t = glm::translate(glm::mat4(), tv);
	glm::mat4 r = glm::rotate(glm::mat4(), rd, rv);
	glm::mat4 s = glm::scale(glm::mat4(), sr);

	glm::mat4 model = t*r*s;
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, glm::value_ptr(model));

	//---------------------------CAMERA
	SetView(glm::lookAt(eye, center, up));

	//DRAW METHOD
	//glPointSize(2.f);
	//glDrawArrays(GL_TRIANGLES, 0, (int)indices.size());
	glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);


	//Unbinding Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//Unbind Vertex Array Object and Shader
	BINDVERTEXARRAY(0);

	//UNBIND SHADER
	glUseProgram(0);

}


#endif /* ModelTexture_h */