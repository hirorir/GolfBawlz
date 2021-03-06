#include "Game.h"
#include "Shader.h"
#include "Camera.h"
#include "Gui.h"
#include <string>

using namespace glm;

int window_width = 512;
int window_height = 512;

float angle = PI;
float power = 1;

Game *game;
GUI *gui;

bool keyState[256] = { false };
bool specialState[256] = { false };

void keyboard() //perform action based on keystates
{
	for (int i = 0; i < 256; i++) {
		if (keyState[i]) {
			vec3 p;
			switch (i) {
			case 'w':
				game->get_current_level()->get_camera()->change_view(rotate(-0.5f, vec3(1.0, 0.0, 0.0)));
				break;
			case 's':
				game->get_current_level()->get_camera()->change_view(rotate(0.5f, vec3(1.0, 0.0, 0.0)));
				break;
			case 'a':
				game->get_current_level()->get_camera()->change_view(rotate(0.5f, vec3(0.0, 0.0, 1.0)));
				break;
			case 'd':
				game->get_current_level()->get_camera()->change_view(rotate(-0.5f, vec3(0.0, 0.0, 1.0)));
				break;
			case 'x':
				game->get_current_level()->get_camera()->change_view(rotate(0.5f, vec3(0.0, 1.0, 0.0)));
				break;
			case 'z':
				game->get_current_level()->get_camera()->change_view(rotate(-0.5f, vec3(0.0, 1.0, 0.0)));
				break;
			case 27:
				exit(0);
				break;
			case 'i':
				if (true) {
					vec3 f = vec3(sin(angle) * power, 0.0f, cos(angle) * power);
					game->get_current_level()->get_ball()->add_force(f);
				}
				break;
			case 'j':
				if (true) {
					vec3 f = vec3(sin(1.5 * angle) * power, 0.0f, cos(1.5 * angle) * power);
					game->get_current_level()->get_ball()->add_force(f);
				}
				break;
			case 'k':
				if (true) {
					vec3 f = vec3(0.0f, 0.0f, power);
					game->get_current_level()->get_ball()->add_force(f);
				}
				break;
			case 'l':
				if (true) {
					vec3 f = vec3(sin(0.5 * angle) * power, 0.0f, cos(0.5 * angle) * power);
					game->get_current_level()->get_ball()->add_force(f);
				}
				break;
			default:
				break;
			}
		}
	}
	glutPostRedisplay();
}

void special(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			game->previous_level();
			break;
		case GLUT_KEY_RIGHT:
			game->next_level();
			break;
		default:
			break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->resize(window_width, window_height);

	keyboard();

	game->update();

	game->draw();

	string course = game->get_current_level()->get_course_name();
	string level = game->get_current_level()->get_level_name();
	string par = game->get_current_level()->get_par();

	gui->draw(course, level, par, to_string(angle), to_string(power));

	glutSwapBuffers();
}

void reshape(int w, int h) 
{
	window_width = w;
	window_height = h;

	game->resize(w, h);
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

	glFrontFace(GL_CCW);
}

void idle(){
	double time_now = game->get_timer().get_elapsed_time();

	if ((time_now - game->get_current_time()) > 0.01666666666f) { // If we exceed the period time (60 FPS).
		game->set_current_time(time_now); // Set new time.
		game->update(); // Update.
	}

	glutPostRedisplay();
}

void keyboard_up(unsigned char c, int x, int y) {
	keyState[c] = false;
}

void keyboard_down(unsigned char c, int x, int y) {
	keyState[c] = true;
	switch (c) {
		case 'v': // Decrease Power
			if ((power - 0.05) > 0.001) {
				power -= 0.05;
			}
			cout << "Power: " << power << endl;
			break;
		case 'b': // Increase Power
			if (power < 1.0) {
				power += 0.05;
			}
			cout << "Power: " << power << endl;
			break;
		case 'm': // Increse Angle
			angle += PI / 180;
			if (angle > 2 * PI) {
				angle -= 2 * PI;
			}
			cout << "Angle: " << angle << endl;
			break;
		case 'n': // Decrease Angle
			angle -= PI / 180;
			if (angle < 0) {
				angle += 2 * PI;
			}
			cout << "Angle: " << angle << endl;
			break;
	}
	glutPostRedisplay();
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
	glutSpecialFunc(special);

	print_opengl_info();
	init_gl();

	game = new Game(argc, argv);
	gui = new GUI("Textures/arrow.png");

	cout << "Power: " << power << endl;
	cout << "Angle: " << angle << endl;

	glutMainLoop();
	
	return 0;
}