#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <vector>

#include "Camera.h"
#include "Level.h"

using namespace std;

class GameManager 
{
public:
	// Constructor.
	explicit GameManager(int argc, char **argv);
		
	// Destructor.
	~GameManager();

	void run();
	void tick();

private:
	//vector<Level> levels;
	//Level current_level;
	//Camera camera;
};

#endif