#include "GameManager.h"
#include "Shader.h"

GameManager *manager;

float speed = 0.1f;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	manager->update();
	manager->draw();
	glutSwapBuffers();
}

void reshape(int w, int h) 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	manager->resize(w, h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		manager->cam->translate(vec3(0, 0, -speed));
		break;
	case 's':
		manager->cam->translate(vec3(0, 0, speed));
		break;
	case 'a':
		manager->cam->translate(vec3(-speed, 0, 0));
		break;
	case 'd':
		manager->cam->translate(vec3(speed, 0, 0));
		break;
	case ' ':
		manager->cam->translate(vec3(0, speed, 0));
		break;
	case 'z':
		manager->cam->translate(vec3(0, -speed, 0));
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void print_opengl_info()
{
	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void idle(){
	display();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Mini Golf");

	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	print_opengl_info();

	manager = new GameManager(argc, argv);

	glutMainLoop();
	
	return 0;
}