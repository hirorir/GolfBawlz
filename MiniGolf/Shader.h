#ifndef SHADER_H
#define SHADER_H 

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include <gl\glew.h>
#include <gl\freeglut.h>
#include <glm\glm.hpp>

#include "Material.h"
#include "Light.h"
#include "Camera.h"

using namespace std;
using namespace glm;

typedef struct ShaderInfo {
	GLchar *string;
	GLsizei byteSize;
	GLenum shaderType;
} sh;

class Shader
{
public:
	Shader(char *vtxPath, char *frgPath);

	void buildProgram(sh *vtx, sh *frg);

	void linkProgram();

	void buildShaderInfo(sh *source, const char *filepathname);

	void readAndCompileShader();

	void set_uniforms(Camera *camera, Light *light, Material *material, mat4 model);

	void use();

	GLuint getProgramHandle();

	void setUniform(const char *name, float x, float y);

	void setUniform(const char *name, float x, float y, float z);

	void setUniform(const char *name, const vec3 &v);

	void setUniform(const char *name, const vec4 &v);

	void setUniform(const char *name, const mat4 &m);

	void setUniform(const char *name, const mat3 &m);

	void setUniform(const char *name, float val);

	void setUniform(const char *name, int val);

	void setUniform(const char *name, bool val);

	void getGLError();

	GLint checkCompileError(GLuint);

private:
	GLuint program_handle;
	char *vertexShaderPath;
	char *fragmentShaderPath;

	int getUniformLocation(const char *name);
};

#endif