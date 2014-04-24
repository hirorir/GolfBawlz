#include "GameManager.h"

GameManager::GameManager(int argc, char **argv)
{
	levels.push_back(FileIO::load_level(argv[1]));
	current_level = 0;

	shader = new Shader("shaders/phong.vert", "shaders/phong.frag");
	shader->readAndCompileShader();
	shader->use();

	cam = new Camera();
}

void GameManager::update()
{
	// TO DO: Translate and rotate level.
	cam->update();
}

void GameManager::draw()
{
	set_matricies();
	levels[current_level].draw();
}


void GameManager::set_matricies()
{
	shader->setUniform("MVP", cam[0].projection * (cam[0].view * cam[0].model));
}

void GameManager::resize(int w, int h){
	cam->resize(w, h);
}

GameManager::~GameManager(){
	delete cam;
}