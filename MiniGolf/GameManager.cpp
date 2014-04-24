#include "GameManager.h"

GameManager::GameManager(int argc, char **argv)
{
	levels.push_back(FileIO::load_level(argv[1]));
	current_level = 0;
}

void GameManager::update()
{
	get_current_level().get_camera()->update();
}

void GameManager::draw()
{
	get_current_level().draw();
}


void GameManager::resize(int w, int h){
	get_current_level().get_camera()->resize(w, h);
}

Level GameManager::get_current_level()
{
	return levels[current_level];
}