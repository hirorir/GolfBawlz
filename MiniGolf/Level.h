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

static const string TILE = "tile";
static const string TEE = "tee";
static const string CUP = "cup";

class Level
{
public:
	Level(vector<Tile*> tiles, Ball *b, Cup *c);

	~Level();

	void update();

	void draw(Camera *camera, Light *light);

	static Level *load_level(string fname);

private:
	vector<Tile*> tiles;
	Ball *ball;
	Cup *cup;
};

#endif