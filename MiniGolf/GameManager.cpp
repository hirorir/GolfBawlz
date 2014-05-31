#include "GameManager.h"

GameManager::GameManager(int argc, char **argv)
{
	levels.push_back(Level::load_level(argv[1]));
	current_level = 0;
	camera = new Camera();
	light = new Light(vec4(0.0f, 5.0f, 0.0f, 1.0f), vec3(0.5f), vec3(1.0f), vec3(1.0f));
	
	timer.start();
	current_time = 0;
}

GameManager::~GameManager()
{
	for (vector<Level*>::size_type i = 0; i < levels.size(); ++i) {
		delete levels[i];
	}
	delete camera;
	delete light;
}

void GameManager::update()
{
	get_current_level()->update();
}

void GameManager::draw()
{
	get_current_level()->draw(camera, light);
}

void GameManager::resize(int w, int h){
	camera->resize(w, h);
}

Level *GameManager::get_current_level() const
{
	return levels[current_level];
}

Camera *GameManager::get_camera() const
{
	return camera;
}

Timer GameManager::get_timer() const
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