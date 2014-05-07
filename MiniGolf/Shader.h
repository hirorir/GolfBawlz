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
	Shader(const char *vtxPath, const char *frgPath);

	void buildProgram(sh *vtx, sh *frg);

	void linkProgram();

	void buildShaderInfo(sh *source, const char *filepathname);

	void readAndCompileShader();

	void use();

	GLuint getProgramHandle();

	void bindAttribLocation(GLuint location, const char * name);

	void bindFragDataLocation(GLuint location, const char * name);

	void setUniform(const char *name, float x, float y);

	void setUniform(const char *name, float x, float y, float z);

	void setUniform(const char *name, const vec3 &v);

	void setUniform(const char *name, const vec4 &v);

	void setUniform(const char *name, const mat4 &m);

	void setUniform(const char *name, const mat3 &m);

	void setUniform(const char *name, float val);

	void setUniform(const char *name, int val);

	void setUniform(const char *name, bool val);

	void printActiveUniforms();

	void printActiveAttribs();

	void getGLError();

	GLint checkCompileError(GLuint);

	const char* getGLErrorString(GLenum error);

	static void set_uniforms_camera(Shader *shader, Camera *camera, mat4 model);

	static void set_uniforms_light(Shader *shader, Camera *camera, Light *light);

	static void set_uniforms_material(Shader *shader, Material mat);

private:
	GLuint program_handle;
	const char *vertexShaderPath;
	const char *fragmentShaderPath;

	int getUniformLocation(const char *name);
};

#endif