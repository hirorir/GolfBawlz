#ifndef TILE_H
#define TILE_H
#include <vector>
#include <glm.hpp>

using namespace std;
using namespace glm;

class Level;				//forward declaration to be defined in Level.h, preventing cyclical header dependencies

class Tile
{
private:
	vector<int> v_indices;	//the indexes of the Vertices in a level that make up this tile
	vector<int> neighbors;	//the indexes of the Tiles in a level that neighbor this tile
	//edge STUB
	void* level;			
	highp_vec3 normal;
	Tile();
public:
	Tile(Level& l);			// Constructor
	~Tile();				// Destructor
};

#endif