#include "GameManager.h"

GameManager::GameManager(int argc, char **argv)
{
	levels.push_back(FileIO::load_level(argv[1]));
	current_level = 0;
	camera = new Camera();
}

void GameManager::tick()
{
	get_current_level().update();
}

void GameManager::draw()
{
	get_current_level().draw(camera);
}

void GameManager::resize(int w, int h){
	camera->resize(w, h);
}

Level GameManager::get_current_level()
{
	return levels[current_level];
}

Camera* GameManager::get_camera()
{
	return camera;
}