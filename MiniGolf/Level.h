#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

#include "Cup.h"
#include "Tee.h"
#include "Tile.h"
#include "Light.h"

using namespace std;

class Level
{
public:
	Level(vector<Tile> tiles, Tee tee, Cup cup);

	void draw();

	void print();

	vector<Tile> get_tiles();

	Tee get_tee();

	Cup get_cup();

	Light get_light();

	void set_light(Light l);

	Tile get_tile_at(int i);

private:
	GLuint vao_handle;
	vector<Tile> tiles;
	Tee tee;
	Cup cup;
	Light light;
};

#endif