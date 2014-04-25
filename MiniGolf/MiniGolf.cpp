#include "GameManager.h"
#include "Shader.h"
#include "Camera.h"

int window_width = 512;
int window_height = 512;

GameManager *manager;
bool keyState[256] = { false };
float speed = 0.1f;

void keyboard()		//perform action based on keystates
{
	for (int i = 0; i < 256; i++)
	{
		if (keyState[i])
			switch (i) {
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
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	keyboard();
	manager->update();
	manager->draw();

	glutSwapBuffers();
}

void reshape(int w, int h) 
{
	manager->resize(w, h);
}

void print_opengl_info()
{
	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void init_gl()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void idle(){
	display();		//when idle, run display func
}

void keyboard_up(unsigned char c, int x, int y){
	keyState[c] = false;
}

void keyboard_down(unsigned char c, int x, int y){
	keyState[c] = true;
}

void mouse(int x, int y){
	static int px = 0;
	static int py = 0;
	Camera::dx = x - px;
	Camera::dy = y - py;
	px = x;
	py = y;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Mini Golf");

	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard_down);
	glutIdleFunc(idle);
	glutKeyboardUpFunc(keyboard_up);
	glutPassiveMotionFunc(mouse);

	print_opengl_info();
	init_gl();

	manager = new GameManager(argc, argv);

	glutMainLoop();
	
	return 0;
}