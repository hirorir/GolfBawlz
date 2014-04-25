#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

#include "Tile.h"
#include "Light.h"
#include "Camera.h"
#include "Object3D.h"
#include "Ball.h"

using namespace std;

class Level
{
public:
	Level(vector<Tile> tiles, Ball b, Object3D c);

	void draw();

	void print();

	void set_uniforms_light();

	void set_uniforms_camera();

	Shader* get_shader();

	Camera* get_camera();

	vector<Tile> get_tiles();

	Light get_light();

	void set_light(Light l);

private:
	Shader *shader;
	Camera *camera;
	vector<Tile> tiles;
	Light light;
	Ball ball;
	Object3D cup;
};

#endif