#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Shader.h"
#include "Level.h"
#include "Player.h"
#include "Tile.h"
#include "Camera.h"
#include "Timer.h"

using namespace std;
using namespace glm;

class Game
{
public:
	Game(int argc, char **argv);

	~Game();

	void update();

	void draw();

	void resize(int w, int h);

	Level *get_current_level() const;

	void next_level();

	void previous_level();

	Timer get_timer() const;

	double get_current_time() const;

	void set_current_time(double t);

private:
	vector<Level*> levels;
	int current_level;
	Player *player;

	// Timer members.
	Timer timer;
	double current_time;
};

#endif