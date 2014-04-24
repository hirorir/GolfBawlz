#include "GameManager.h"
#include "Shader.h"

GameManager *manager;

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
		cout << "w pressed!" << endl;
		break;
	case 's':
		cout << "s pressed!" << endl;
		break;
	case 'a':
		cout << "a pressed!" << endl;
		break;
	case 'd':
		cout << "d pressed!" << endl;
		break;
	case ' ':
		cout << "space pressed!" << endl;
		break;
	case 'z':
		cout << "z pressed!" << endl;
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

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Mini Golf");

	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	print_opengl_info();

	manager = new GameManager(argc, argv);

	glutMainLoop();
	
	return 0;
}