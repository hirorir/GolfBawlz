#pragma once

#ifndef GLSUPPORT_H
#define GLSUPPORT_H

#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/projection.hpp>

using namespace glm;
using namespace std;

#define PI 3.141592653589793
#define TWOPI 6.2831853071795862
#define TO_RADIANS(x) (x * 0.017453292519943295)
#define TO_DEGREES(x) (x * 57.29577951308232)

// Check if there has been an error inside OpenGL and if yes, print the error and
// through a runtime_error exception.
void checkGlErrors();

// Reads and compiles a pair of vertex shader and fragment shader files into a
// GL shader program. Throws runtime_error on error
void readAndCompileShader(GLuint programHandle, const char *vertexShaderFileName, const char *fragmentShaderFileName);

// Reads and compiles a single shader (vertex, fragment, etc) file into a GL
// shader. Throws runtime_error on error
void readAndCompileSingleShader(GLuint shaderHandle, const char* shaderFileName);

// Uniform helpers
void setUniform(GLuint programHandle, const char *name, float x, float y, float z);
void setUniform(GLuint programHandle, const char *name, const vec4 & v);
void setUniform(GLuint programHandle, const char *name, const mat4 & m);
void setUniform(GLuint programHandle, const char *name, const mat3 & m);
void setUniform(GLuint programHandle, const char *name, float val);

// Utils
static int checkForOpenGLError(const char *, int);
static void dumpGLInfo(bool dumpExtensions = false);

// Classes inheriting Noncopyable will not have default compiler generated copy
// constructor and assignment operator
class Noncopyable {
protected:
  Noncopyable() {}
  ~Noncopyable() {}
private:
  Noncopyable(const Noncopyable&);
  const Noncopyable& operator= (const Noncopyable&);
};

// Light wrapper around a GL shader (can be geometry/vertex/fragment shader)
// handle. Automatically allocates and deallocates. Can be casted to GLuint.
class GlShader : Noncopyable {
  GLuint handle;

public:
  GlShader(GLenum shaderType) {
    handle = glCreateShader(shaderType); // create shader handle
    if (handle == 0)
      throw std::runtime_error("glCreateShader fails");
    checkGlErrors();
  }

  ~GlShader() {
    glDeleteShader(handle);
  }

  // Casts to GLuint so can be used directly by glCompile etc
  operator GLuint() const {
    return handle;
  }
};

// Light wrapper around GLSL program handle that automatically allocates
// and deallocates. Can be casted to a GLuint.
class GlProgram : Noncopyable {
  GLuint handle;

public:
  GlProgram() {
    handle = glCreateProgram();
    if (handle == 0)
      throw std::runtime_error("glCreateProgram fails");
    checkGlErrors();
  }

  ~GlProgram() {
    glDeleteProgram(handle);
  }

  // Casts to GLuint so can be used directly by glUseProgram and so on
  operator GLuint() const {
    return handle;
  }
};


// Light wrapper around a GL texture object handle that automatically allocates
// and deallocates. Can be casted to a GLuint.
class GlTexture : Noncopyable {
  GLuint handle;

public:
  GlTexture() {
    glGenTextures(1, &handle);
    checkGlErrors();
  }

  ~GlTexture() {
    glDeleteTextures(1,&handle);
  }

  // Casts to GLuint so can be used directly by glBindTexture and so on
  operator GLuint () const {
    return handle;
  }
};

// Light wrapper around a GL buffer object handle that automatically allocates
// and deallocates. Can be casted to a GLuint.
class GlBufferObject : Noncopyable {
  GLuint handle;

public:
  GlBufferObject() {
    glGenBuffers(1, &handle);
    checkGlErrors();
  }

  ~GlBufferObject() {
    glDeleteBuffers(1, &handle);
  }

  // Casts to GLuint so can be used directly glBindBuffer and so on
  operator GLuint() const {
    return handle;
  }
};

// Safe versions of various functions that handle GLSL shader attributes
// and variables: These mainly issue a warning when specified attributes
// and variables do not exist in the compiled GLSL program (e.g., due to
// driver optimization), and return without doing anything when the user
// tries to change these attributes or variables.

inline GLint safe_glGetUniformLocation(const GLuint program, const char varname[]) {
  GLint r = glGetUniformLocation(program, varname);
  if (r < 0)
    std::cerr << "WARN: "<< varname << " cannot be bound (it either doesn't exist or has been optimized away). safe_glUniform calls will silently ignore it.\n" << std::endl;
  return r;
}

inline GLint safe_glGetAttribLocation(const GLuint program, const char varname[]) {
  GLint r = glGetAttribLocation(program, varname);
  if (r < 0)
    std::cerr << "WARN: "<< varname << " cannot be bound (it either doesn't exist or has been optimized away). safe_glAttrib calls will silently ignore it.\n" << std::endl;
  return r;
}

inline void safe_glUniformMatrix4fv(const GLint handle, const GLfloat data[]) {
  if (handle >= 0)
    glUniformMatrix4fv(handle, 1, GL_FALSE, data);
}

inline void safe_glUniform1i(const GLint handle, const GLint a) {
  if (handle >= 0)
    glUniform1i(handle, a);
}

inline void safe_glUniform2i(const GLint handle, const GLint a, const GLint b) {
  if (handle >= 0)
    glUniform2i(handle, a, b);
}

inline void safe_glUniform3i(const GLint handle, const GLint a, const GLint b, const GLint c) {
  if (handle >= 0)
    glUniform3i(handle, a, b, c);
}

inline void safe_glUniform4i(const GLint handle, const GLint a, const GLint b, const GLint c, const GLint d) {
  if (handle >= 0)
    glUniform4i(handle, a, b, c, d);
}

inline void safe_glUniform1f(const GLint handle, const GLfloat a) {
  if (handle >= 0)
    glUniform1f(handle, a);
}

inline void safe_glUniform2f(const GLint handle, const GLfloat a, const GLfloat b) {
  if (handle >= 0)
    glUniform2f(handle, a, b);
}

inline void safe_glUniform3f(const GLint handle, const GLfloat a, const GLfloat b, const GLfloat c) {
  if (handle >= 0)
    glUniform3f(handle, a, b, c);
}

inline void safe_glUniform4f(const GLint handle, const GLfloat a, const GLfloat b, const GLfloat c, const GLfloat d) {
  if (handle >= 0)
    glUniform4f(handle, a, b, c, d);
}

inline void safe_glEnableVertexAttribArray(const GLint handle) {
  if (handle >= 0)
    glEnableVertexAttribArray(handle);
}

inline void safe_glDisableVertexAttribArray(const GLint handle) {
  if (handle >= 0)
    glDisableVertexAttribArray(handle);
}

inline void safe_glVertexAttribPointer(const GLint handle, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) {
  if (handle >= 0)
    glVertexAttribPointer(handle, size, type, normalized, stride, pointer);
}

inline void safe_glVertexAttrib1f(const GLint handle, const GLfloat a) {
  if (handle >= 0)
    glVertexAttrib1f(handle, a);
}

inline void safe_glVertexAttrib2f(const GLint handle, const GLfloat a, const GLfloat b) {
  if (handle >= 0)
    glVertexAttrib2f(handle, a, b);
}

inline void safe_glVertexAttrib3f(const GLint handle, const GLfloat a, const GLfloat b, const GLfloat c) {
  if (handle >= 0)
    glVertexAttrib3f(handle, a, b, c);
}

inline void safe_glVertexAttrib4f(const GLint handle, const GLfloat a, const GLfloat b, const GLfloat c, const GLfloat d) {
  if (handle >= 0)
    glVertexAttrib4f(handle, a, b, c, d);
}

inline void safe_glVertexAttrib4Nub(const GLint handle, const GLubyte a, const GLubyte b, const GLubyte c, const GLubyte d) {
  if (handle >= 0)
    glVertexAttrib4Nub(handle, a, b, c, d);
}

#endif