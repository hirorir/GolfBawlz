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
	manager->resize(w, h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		manager->get_current_level().get_camera()->translate(vec3(0, 0, -speed));
		break;
	case 's':
		manager->get_current_level().get_camera()->translate(vec3(0, 0, speed));
		break;
	case 'a':
		manager->get_current_level().get_camera()->translate(vec3(-speed, 0, 0));
		break;
	case 'd':
		manager->get_current_level().get_camera()->translate(vec3(speed, 0, 0));
		break;
	case ' ':
		manager->get_current_level().get_camera()->translate(vec3(0, speed, 0));
		break;
	case 'z':
		manager->get_current_level().get_camera()->translate(vec3(0, -speed, 0));
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
	cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl << endl;
}

void init_gl()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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
	init_gl();

	manager = new GameManager(argc, argv);

	glutMainLoop();
	
	return 0;
}