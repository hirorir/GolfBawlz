#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

#include "glsupport.h"

void checkGlErrors() {
  const GLenum errCode = glGetError();

  if (errCode != GL_NO_ERROR) {
    string error("GL Error: ");
    error += reinterpret_cast<const char*>(gluErrorString(errCode));
    cerr << error << endl;
    throw runtime_error(error);
  }
}

// Dump text file into a character vector, throws exception on error
static void readTextFile(const char *fn, vector<char>& data) {
  // Sets ios::binary bit to prevent end of line translation, so that the
  // number of bytes we read equals file size
  ifstream ifs(fn, ios::in | ios::binary);

  // Sets bits to report IO error using exception
  ifs.exceptions(ios::eofbit | ios::failbit | ios::badbit);
  ifs.seekg(0, ios::end);
  size_t len = ifs.tellg();

  data.resize(len);

  ifs.seekg(0, ios::beg);
  ifs.read(&data[0], len);
}

// Print info regarding an GL object
static void printInfoLog(GLuint obj, const string& filename) {
  GLint infologLength = 0;
  GLint charsWritten  = 0;
  glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);
  if (infologLength > 0) {
    string infoLog(infologLength, ' ');
    glGetInfoLogARB(obj, infologLength, &charsWritten, &infoLog[0]);
    std::cerr << "##### Log [" << filename << "]:\n" << infoLog << endl;
  }
}

void readAndCompileSingleShader(GLuint shaderHandle, const char *fn) {
  vector<char> source;
  readTextFile(fn, source);

  const char *ptrs[] = {&source[0]};
  const GLint lens[] = {source.size()};
  glShaderSource(shaderHandle, 1, ptrs, lens);   // load the shader sources

  glCompileShader(shaderHandle);

  printInfoLog(shaderHandle, fn);

  GLint compiled = 0;
  glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
  if (!compiled)
    throw runtime_error("fails to compile GL shader");
}

void readAndCompileShader(GLuint programHandle, const char * vertexShaderFileName, const char * fragmentShaderFileName) {
  GlShader vs(GL_VERTEX_SHADER);
  GlShader fs(GL_FRAGMENT_SHADER);

  readAndCompileSingleShader(vs, vertexShaderFileName);
  readAndCompileSingleShader(fs, fragmentShaderFileName);

  glAttachShader(programHandle, vs);
  glAttachShader(programHandle, fs);

  glLinkProgram(programHandle);

  glDetachShader(programHandle, vs);
  glDetachShader(programHandle, fs);

  GLint linked = 0;
  glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);
  printInfoLog(programHandle, "linking");

  if (!linked)
    throw runtime_error("fails to link shaders");
}

void setUniform(GLuint programHandle, const char *name, float x, float y, float z) {
    int loc = glGetUniformLocation(programHandle, name);

    if( loc >= 0 ) {
        glUniform3f(loc,x,y,z);
    }
}

void setUniform(GLuint programHandle, const char *name, const vec4 & v) {
    int loc = glGetUniformLocation(programHandle, name);

    if( loc >= 0 ) {
        glUniform4f(loc,v.x,v.y,v.z,v.w);
    }
}

void setUniform(GLuint programHandle, const char *name, float val) {
    int loc =glGetUniformLocation(programHandle, name);
    if( loc >= 0 )
    {
        glUniform1f(loc, val);
    }
}

void setUniform(GLuint programHandle, const char *name, const mat4 & m) {
    int loc = glGetUniformLocation(programHandle, name);

    if( loc >= 0 ) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
    }
}

void setUniform(GLuint programHandle, const char *name, const mat3 & m) {
    int loc =  glGetUniformLocation(programHandle, name);

    if( loc >= 0 ) {
        glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
    }
}

int checkForOpenGLError(const char * file, int line) {
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;

}

void dumpGLInfo(bool dumpExtensions) {
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor    : %s\n", vendor);
    printf("GL Renderer  : %s\n", renderer);
    printf("GL Version   : %s\n", version);
    printf("GL Version   : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    if( dumpExtensions ) {
        GLint nExtensions;
        glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
        for( int i = 0; i < nExtensions; i++ ) {
            printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
        }
    }
}