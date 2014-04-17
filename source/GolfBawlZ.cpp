#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>

#include <GL/glew.h>
#ifdef __MAC__
#   include <GLUT/freeglut.h>
#else
#   include <GL/freeglut.h>
#endif

#include "ppm.h"
#include "glsupport.h"

using namespace std;

// application globals
static int g_width             = 512;         // screen width
static int g_height            = 512;         // screen height
static bool g_leftClicked       = false;      // is the left mouse button down?
static bool g_rightClicked      = false;      // is the right mouse button down?
static float g_objScale          = 1.0;       // scale factor for object
static int g_leftClickX, g_leftClickY;        // coordinates for mouse left click event
static int g_rightClickX, g_rightClickY;      // coordinates for mouse right click event

// OpenGL non-shader handles
static GLuint h_texture;                                   // textures
static GLuint h_sqVertVbo, h_sqTexCoordVbo, h_sqColorVbo;   // vertex buffer objects

// Shader globals
static GLuint h_program;     // handle to OpenGL program object

// handles to vertex attributes (note the `a' prefix)
static GLuint h_aTexCoord;
static GLuint h_aVertex;
static GLuint h_aColor;

// handles to uniform variables (note the `u' prefix)
static GLint h_uTexUnit0;        // texture unit variable
static GLint h_uVertexScale;     // horizontal scaling factor for the square

static void drawObj(GLuint vertbo, GLuint texbo, GLuint colbo, int numverts) {
  safe_glEnableVertexAttribArray(h_aVertex);
  safe_glEnableVertexAttribArray(h_aTexCoord);
  safe_glEnableVertexAttribArray(h_aColor);

  glBindBuffer(GL_ARRAY_BUFFER,vertbo);
  safe_glVertexAttribPointer(h_aVertex, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER,texbo);
  safe_glVertexAttribPointer(h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER,colbo);
  safe_glVertexAttribPointer(h_aColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES,0,numverts);

  safe_glDisableVertexAttribArray(h_aVertex);
  safe_glDisableVertexAttribArray(h_aColor);
  safe_glDisableVertexAttribArray(h_aTexCoord);
}

static void display(void) {
  glUseProgram(h_program);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  safe_glUniform1i(h_uTexUnit0, 0);
  safe_glUniform1f(h_uVertexScale, g_objScale);

  drawObj(h_sqVertVbo, h_sqTexCoordVbo, h_sqColorVbo, 6);

  glutSwapBuffers();

  // check for errors
  checkGlErrors();
}

static void reshape(int w, int h) {
  g_width = w;
  g_height = h;
  glViewport(0, 0, w, h);
  glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      // right mouse button has been clicked
      g_leftClicked = true;
      g_leftClickX = x;
      g_leftClickY = g_height - y - 1;
    }
    else {
      // right mouse button has been released
      g_leftClicked = false;
    }
  }
}


static void motion(int x, int y) {
  const int newx = x;
  const int newy = g_height - y - 1;
  if (g_leftClicked) {
    float deltax = (newx - g_leftClickX) * 0.02;
    g_objScale += deltax;
    
    g_leftClickX = newx;
    g_leftClickY = newy;
  }
  glutPostRedisplay();
}

static void initGlutState(int argc, char **argv) {
  glutInit(&argc,argv); 
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(g_width, g_height);   
  glutCreateWindow("Test"); 

  glutDisplayFunc(display);                
  glutReshapeFunc(reshape);                
  glutMotionFunc(motion);                  
  glutMouseFunc(mouse);                    
}

static void initGLState() {
  glClearColor(128./255,200./255,1,0);
  glEnable(GL_FRAMEBUFFER_SRGB);
}

static void initShaders() {
  h_program = glCreateProgram();
  readAndCompileShader(h_program, "../shaders/asst1-gl3.vshader", 
             "../shaders/asst1-gl3.fshader");

  glBindFragDataLocation(h_program, 0, "fragColor");

  // grab handles to the shader variables by name
  h_aVertex = safe_glGetAttribLocation(h_program, "aVertex");
  h_aColor = safe_glGetAttribLocation(h_program, "aColor");

  h_aTexCoord = safe_glGetAttribLocation(h_program, "aTexCoord");
  h_uTexUnit0 = safe_glGetUniformLocation(h_program, "uTexUnit0");
  h_uVertexScale = safe_glGetUniformLocation(h_program, "uVertexScale");
}

static void initVBOs() {
  GLfloat sqVerts[12] = {
    -.5, -.5,
    .5,  .5,
    .5,  -.5,

    -.5, -.5,
    -.5, .5,
    .5,  .5
  };

  GLfloat sqCol[18] =  {
    1, 0, 0,
    0, 1, 1,
    0, 0, 1,

    1, 0, 0,
    0, 1, 0,
    0, 1, 1
  };

  GLfloat sqTex[12] = {
    0, 0,
    1,  1,
    1,  0,

    0, 0,
    0, 1,
    1,  1
  };


  glGenBuffers(1,&h_sqVertVbo);
  glBindBuffer(GL_ARRAY_BUFFER,h_sqVertVbo);
  glBufferData(
    GL_ARRAY_BUFFER,
    12*sizeof(GLfloat),
    sqVerts,
    GL_STATIC_DRAW);


  glGenBuffers(1,&h_sqColorVbo);
  glBindBuffer(GL_ARRAY_BUFFER,h_sqColorVbo);
  glBufferData(
    GL_ARRAY_BUFFER,
    18*sizeof(GLfloat),
    sqCol,
    GL_STATIC_DRAW);

  glGenBuffers(1,&h_sqTexCoordVbo);
  glBindBuffer(GL_ARRAY_BUFFER,h_sqTexCoordVbo);
  glBufferData(
    GL_ARRAY_BUFFER,
    12*sizeof(GLfloat),
    sqTex,
    GL_STATIC_DRAW);

}

static void initTextures() {

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &h_texture);
  glBindTexture(GL_TEXTURE_2D, h_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  int twidth, theight;
  vector<PackedPixel> pixData;
  ppmRead("../data/reachup.ppm", twidth, theight, pixData);


  glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, twidth, theight, 
          0, GL_RGB, GL_UNSIGNED_BYTE, &pixData[0]);
}

int main(int argc, char **argv) {

  initGlutState(argc,argv);
  glewInit();  
  
  if (!GLEW_VERSION_3_0) {
    cerr << "Error: card/driver does not support OpenGL Shading Language v1.3\n";
    return -1;
  }

  initGLState();
  initShaders();
  initVBOs();
  initTextures();

  glutMainLoop();

  return 0;
}