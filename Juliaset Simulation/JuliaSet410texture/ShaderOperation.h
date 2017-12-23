
#ifndef ShaderOperation_h
#define ShaderOperation_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    
    GLuint sID;
    
public:
    
    GLuint id() const { return sID; }
    Shader(char *vpath, char *fpath);
    Shader(const char * vert, const char * frag);
    void compilerCheck(GLuint ID);
    void linkCheck(GLuint ID);
    void bind();
    void unbind();
};

Shader::Shader(const char * vert, const char * frag)
{
    /*-----------------------------------------------------------------------------
     *  CREATE THE SHADER PROGRAM
     *-----------------------------------------------------------------------------*/

    sID = glCreateProgram();
    GLuint vID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vID, 1, &vert, NULL); 
    glShaderSource(fID, 1, &frag, NULL);
    
    glCompileShader(vID);
    glCompileShader(fID);

    compilerCheck(vID);
    compilerCheck(fID);
    
    glAttachShader(sID,vID);
    glAttachShader(sID,fID);
    

    glLinkProgram(sID);

    linkCheck(sID);

    glUseProgram(sID);
}
Shader::Shader(char *vpath, char *fpath)
{
    try {
        /*-----------------------------------------------------------------------------
         *  Reading Shaders
         *-----------------------------------------------------------------------------*/
        
        std::string vertexCode;
        std::string fragmentCode;
        
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        
        //char *vpath = (char *)"/Users/sophie/Downloads/Xcode/OpenGLExercises/JuliaSet/vertex.vs";
        vShaderFile.open(vpath);
        
        //char *fpath = (char *)"/Users/sophie/Downloads/Xcode/OpenGLExercises/JuliaSet/frag.fs";
        fShaderFile.open(fpath);
        
        std::stringstream vShaderStream, fShaderStream;
        
     
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();
  
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
        const char* vert = vertexCode.c_str();
        const char * frag = fragmentCode.c_str();
        
            
        
        
        /*-----------------------------------------------------------------------------
         *  CREATE THE SHADER PROGRAM
         *-----------------------------------------------------------------------------*/

        sID = glCreateProgram();
        GLuint vID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vID, 1, &vert, NULL); 
        glShaderSource(fID, 1, &frag, NULL);

        glCompileShader(vID);
        glCompileShader(fID);

        compilerCheck(vID);
        compilerCheck(fID);
        
        glAttachShader(sID,vID);
        glAttachShader(sID,fID);
       
        glLinkProgram(sID);

        linkCheck(sID);

        glUseProgram(sID);
        
    }
    catch (exception e)
    {
        cout<<"SOMTHING IS WRONG WITH THE FILE"<<endl;
        cout<<e.what()<<endl;

    }
   
}

void Shader::compilerCheck(GLuint ID)
{
    GLint comp;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);
    
    if(comp == GL_FALSE ){
        cout << "Shader Compilation FAILED" << endl;
        GLchar messages[256];
        glGetShaderInfoLog(ID, sizeof(messages),0,&messages[0]);
        cout << messages;
    }
}
void Shader::linkCheck(GLuint ID)
{
    GLint linkStatus, validateStatus;
    glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);
    
    
    if(linkStatus == GL_FALSE ){
        cout << "Shader Linking FAILED" << endl;
        GLchar messages[256];
        glGetProgramInfoLog(ID, sizeof(messages),0,&messages[0]);
        cout << messages;
    }
    
    glValidateProgram(ID);
    glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);
    
    cout << "Link: " << linkStatus << "  Validate: " << validateStatus << endl;
    if(linkStatus == GL_FALSE ){
        cout << "Shader Validation FAILED" << endl;
        GLchar messages[256];
        glGetProgramInfoLog(ID, sizeof(messages),0,&messages[0]);
        cout << messages;
    }
    
}
void Shader::bind()
{ glUseProgram(sID); }
void Shader::unbind()
{ glUseProgram(0); }

#endif /* ShaderOperation_h */
