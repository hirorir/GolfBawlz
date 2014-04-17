#include <iostream>

#include "glsupport.h"
#include "vbotorus.h"
#include "vboteapot.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/projection.hpp>

using namespace glm;
using namespace std;

GLuint program;
VBOTorus *torus;
VBOTeapot *teapot;
VBOTeapot *teapot2;

mat4 model;
mat4 view;
mat4 projection;

void setMatrices() {
    mat4 mv = view * model;
    setUniform(program, "ModelViewMatrix", mv);
    setUniform(program, "NormalMatrix", mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    setUniform(program, "MVP", projection * mv);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GLuint adsIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "phongModel");
	//GLuint diffuseIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "diffuseOnly");

	//glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &adsIndex);
	setMatrices();
	teapot->render();

	//model *= translate(mat4(1.0f), vec3(-5.0, 5.0, 0.0));

	//setMatrices();
	//glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &diffuseIndex);
	//teapot2->render();
	glutSwapBuffers();
	//glutPostRedisplay();
}

void initProgram() {
	program = glCreateProgram();
	readAndCompileShader(program, "diffuse.vert", "diffuse.frag");
	glUseProgram(program);

	glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);

    //torus = new VBOTorus(0.7f, 0.3f, 50, 50);
	mat4 transform = translate(mat4(1.0f), vec3(0.0f,0.0f,0.0f));
	teapot = new VBOTeapot(15, transform);
	//teapot2 = new VBOTeapot(15, transform);

    model = mat4(1.0f);
    //model *= rotate(-25.0f, vec3(1.0f,0.0f,0.0f));
    model *= rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	model *= translate(mat4(1.0f), vec3(0.0f, 0.0f, -2.0f));
    view = lookAt(vec3(0.0f,1.0f,6.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    projection = mat4(1.0f);

    /*setUniform(program, "Kd", 0.9f, 0.5f, 0.3f);
    setUniform(program, "Ld", 1.0f, 1.0f, 1.0f);
	setUniform(program, "LightPosition", view * vec4(5.0f,5.0f,2.0f,1.0f) );*/

    setUniform(program, "Light.Position", view * vec4(5.0f,5.0f,2.0f,1.0f) );
	setUniform(program, "Material.Ka", 0.9f, 0.5f, 0.3f);
    setUniform(program, "Light.La", 0.4f, 0.4f, 0.4f);
	setUniform(program, "Material.Kd", 0.9f, 0.5f, 0.3f);
    setUniform(program, "Light.Ld", 1.0f, 1.0f, 1.0f);
    setUniform(program, "Material.Ks", 0.8f, 0.8f, 0.8f);
    setUniform(program, "Light.Ls", 1.0f, 1.0f, 1.0f);
    setUniform(program, "Material.Shininess", 100.0f);
}

void reshape(int w, int h) {
	glViewport(0,0,w,h);
	projection = perspective(70.0f, (float)w/h, 0.3f, 100.0f);
}

void keyboard(unsigned char key,int x, int y) {
	switch (key) {
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

int main( int argc, char **argv ) {
	glutInit(&argc, argv);

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize( 512, 512 );
	glutCreateWindow("ShaderTest");
	glewInit();

	initProgram();

	glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    glutMainLoop();

	return 0;
}