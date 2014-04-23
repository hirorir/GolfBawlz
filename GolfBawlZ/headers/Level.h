#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <glm.hpp>

#include "../headers/Tile.h"

using namespace std;
using namespace glm;

class Level
{
private:
	vector<highp_vec3> vertices;	//vector of vertices that this level contains
	vector<Tile> tiles;				//vector of Tiles that this level contains

public:
	explicit Level();		// Constructor.
	~Level();				// Destructor.
};

#endif