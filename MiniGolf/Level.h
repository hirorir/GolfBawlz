#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

#include "Shader.h"
#include "Tile.h"
#include "Light.h"
#include "Camera.h"
#include "Ball.h"
#include "Cup.h"

using namespace std;

class Level
{
public:
	Level(vector<Tile> tiles, Ball b, Cup c);

	void update();

	void draw(Camera *camera);

	void print();

	vector<Tile> get_tiles();

	Light* get_light();

	void set_light(Light *l);

	Ball get_ball();

private:
	vector<Tile> tiles;
	Light *light;
	Ball ball;
	Cup cup;
};

#endif