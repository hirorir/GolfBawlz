 #include "GameManager.h"

GameManager::GameManager(int argc, char **argv)
{
	levels.push_back(FileIO::load_level(argv[1]));
	current_level = 0;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	shader = new Shader("shaders/phong.vert", "shaders/phong.frag");
	shader->readAndCompileShader();
	shader->use();

	cam = new Camera();

	shader->setUniform("Material.Kd", 0.2f, 0.9f, 0.2f);
	shader->setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
	shader->setUniform("Light.Position", view * vec4(5.0f, 5.0f, 2.0f, 1.0f));
	shader->setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
	shader->setUniform("Light.La", 0.4f, 0.4f, 0.4f);
	shader->setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
	shader->setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
	shader->setUniform("Material.Shininess", 100.0f);
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
	mat4 mv = (cam[0].view * cam[0].model);
	shader->setUniform("ModelViewMatrix", mv);
	shader->setUniform("NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	shader->setUniform("MVP", cam[0].projection * mv);
}

void GameManager::resize(int w, int h){
	cam->resize(w, h);
}

GameManager::~GameManager(){
	delete cam;
}