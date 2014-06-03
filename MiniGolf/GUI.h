#include <iostream>
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <glm\glm.hpp>
#include <string>

#include "SOIL\SOIL.h"

using namespace std;

class GUI{
public:
	GLuint texture;

	void draw();
	void loadTexture(string path);
	GUI(string path);
};