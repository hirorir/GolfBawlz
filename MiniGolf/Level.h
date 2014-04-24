#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

#include "Cup.h"
#include "Tee.h"
#include "Tile.h"
#include "Light.h"
#include "Camera.h"

using namespace std;

class Level
{
public:
	Level(vector<Tile> tiles, Tee tee, Cup cup);

	void draw();

	void print();

	void set_uniforms_light();

	void set_uniforms_camera();

	Shader* get_shader();

	Camera* get_camera();

	vector<Tile> get_tiles();

	Tee get_tee();

	Cup get_cup();

	Light get_light();

	void set_light(Light l);

private:
	Shader *shader;
	Camera *camera;
	vector<Tile> tiles;
	Tee tee;
	Cup cup;
	Light light;

	void set_uniforms_tile(Tile tile);
};

#endif