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
#include "Timer.h"

using namespace std;
using namespace glm;

class GameManager
{
public:
	GameManager(int argc, char **argv);

	~GameManager();

	void update();

	void draw();

	void resize(int w, int h);

	Level *get_current_level();

	Camera *get_camera();

	Timer get_timer();

	double get_current_time() const;

	void set_current_time(double t);

private:
	vector<Level*> levels;
	Camera *camera;
	int current_level;

	// Timer members.
	Timer timer;
	double current_time;
};

#endif