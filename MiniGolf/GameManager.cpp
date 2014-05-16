#include "GameManager.h"

GameManager::GameManager(int argc, char **argv)
{
	levels.push_back(FileIO::load_level(argv[1]));
	current_level = 0;
	camera = new Camera();
	
	timer.start();
	current_time = 0;
}

GameManager::~GameManager()
{
	for (vector<Level*>::size_type i = 0; i < levels.size(); ++i) {
		delete levels[i];
	}
	delete camera;
}

void GameManager::update()
{
	get_current_level()->update();
}

void GameManager::draw()
{
	get_current_level()->draw(camera);
}

void GameManager::resize(int w, int h){
	camera->resize(w, h);
}

Level *GameManager::get_current_level()
{
	return levels[current_level];
}

Camera* GameManager::get_camera()
{
	return camera;
}

Timer GameManager::get_timer()
{
	return timer;
}

double GameManager::get_current_time() const
{
	return  current_time;
}

void GameManager::set_current_time(double t)
{
	current_time = t;
}