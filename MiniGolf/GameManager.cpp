#include "GameManager.h"

GameManager::GameManager(int argc, char **argv)
{
	levels.push_back(FileIO::load_level(argv[1]));
	current_level = 0;

	shader = new Shader("shaders/phong.vert", "shaders/phong.frag");
	shader->readAndCompileShader();
	shader->use();

	model = mat4(1.0f);
	view = lookAt(vec3(0.0f, 0.5f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
}

void GameManager::update()
{
	// TO DO: Translate and rotate level.
}

void GameManager::draw()
{
	set_matricies();
	levels[current_level].draw();
}


void GameManager::set_matricies()
{
	mat4 mv = view * model;
	shader->setUniform("MVP", projection * mv);
}

void GameManager::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	projection = perspective(70.0f, (float)w / h, 0.3f, 100.0f);
}