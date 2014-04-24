#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Shader.h"
#include "Level.h"
#include "Tile.h"
#include "FileIO.h"
#include "Camera.h"

using namespace std;
using namespace glm;

class GameManager
{
public:
	GameManager(int argc, char **argv);

	~GameManager();

	void update();

	void draw();

	void set_matricies();

	void resize(int w, int h);

	Camera *cam;

private:
	Shader *shader;
	vector<Level> levels;
	int current_level;

	mat4 model;
	mat4 view;
	mat4 projection;
};

#endif