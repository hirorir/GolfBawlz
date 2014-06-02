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
#include "Tee.h"

using namespace std;

static const string TILE = "tile";
static const string TEE = "tee";
static const string CUP = "cup";
static const string COURSE = "course";
static const string BEGIN_HOLE = "begin_hole";
static const string END_HOLE = "end_hole";
static const string NAME = "name";
static const string PAR = "par";

class Level
{
public:
	Level(vector<Tile*> tiles, Ball *b, Cup *c, Tee *tee, string course_name, string level_name, int par);

	~Level();

	void update();

	void draw();

	Camera *get_camera() const;

	Ball *get_ball() const;

	string get_course_name() const;

	string get_level_name() const;

	int get_par() const;

	vector<Tile*> get_tiles() const;

	void print() const;

	static vector<Level*> load_levels(string fname);

	void Level::set_ball_tile(vec3 point);

private:
	vector<Tile*> tiles;
	Camera *camera;
	Light *light;
	Ball *ball;
	Cup *cup;
	Tee *tee;
	string course_name;
	string level_name;
	int par;
};

#endif