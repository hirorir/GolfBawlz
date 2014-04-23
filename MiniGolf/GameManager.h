#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include <glm\gtx\transform.hpp>

#include "Shader.h"
#include "Level.h"
#include "Tile.h"
#include "FileIO.h"

using namespace std;

class GameManager
{
public:
	GameManager(int argc, char **argv);

	void update();

	void draw();

	void set_matricies();

	void resize(int w, int h);

private:
	Shader *shader;
	vector<Level> levels;
	int current_level;

	mat4 model;
	mat4 view;
	mat4 projection;
};

#endif