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

using namespace std;
using namespace glm;

typedef struct ShaderInfo {
	GLchar *string;
	GLsizei byteSize;
	GLenum shaderType;
} sh;

class Shader {
private:
	GLuint programHandle;
	const char *vertexShaderPath;
	const char *fragmentShaderPath;

	int getUniformLocation(const char *name);
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

	static inline const char* getGLErrorString(GLenum error) {
		const char *str;
		switch (error) {
		case GL_NO_ERROR:
			str = "GL_NO_ERROR";
			break;
		case GL_INVALID_ENUM:
			str = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			str = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			str = "GL_INVALID_OPERATION";
			break;
#if defined __gl_h_ || defined __gl3_h_
		case GL_OUT_OF_MEMORY:
			str = "GL_OUT_OF_MEMORY";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			str = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
#endif
#if defined __gl_h_
		case GL_STACK_OVERFLOW:
			str = "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			str = "GL_STACK_UNDERFLOW";
			break;
		case GL_TABLE_TOO_LARGE:
			str = "GL_TABLE_TOO_LARGE";
			break;
#endif
		default:
			str = "(ERROR: Unknown Error Enum)";
			break;
		}
		return str;
	}
};

#endif