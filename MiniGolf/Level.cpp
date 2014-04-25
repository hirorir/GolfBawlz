#include "Level.h"

Level::Level(vector<Tile> tiles, Ball b, Object3D c)
{
	this->tiles = tiles;
	this->light = Light(vec4(0.0f, 5.0f, 0.0f, 1.0f), vec3(0.5f), vec3(1.0f), vec3(1.0f));
	this->ball = b;
	this->cup = c;

	shader = new Shader("shaders/phong.vert", "shaders/phong.frag");
	shader->readAndCompileShader();
	shader->use();

	camera = new Camera();

	ball.init_gl();
	cup.init_gl();

	print();
}

void Level::draw()
{
	set_uniforms_light();

	set_uniforms_camera();

	for (vector<Tile>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i].draw(shader);
	}

	camera[0].model *= translate(vec3(ball.get_position().x, ball.get_position().y + 0.05, ball.get_position().z));
	camera[0].model *= scale(vec3(0.2f));

	set_uniforms_camera();

	ball.draw(shader);

	camera[0].model = mat4(1.0f);

	camera[0].model *= translate(vec3(cup.get_position().x, cup.get_position().y - 0.09, cup.get_position().z));
	camera[0].model *= scale(vec3(0.2f));

	set_uniforms_camera();

	cup.draw(shader);

	camera[0].model = mat4(1.0f);

	set_uniforms_camera();
}

void Level::print()
{
	for (vector<Tile>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i].print();
	}

	cout << "BALL: "; ball.print();
	cout << "CUP: "; cup.print();
}

void Level::set_uniforms_light()
{
	shader->setUniform("Light.La", light.get_ambient());
	shader->setUniform("Light.Ld", light.get_diffuse());
	shader->setUniform("Light.Ls", light.get_specular());
	shader->setUniform("Light.Position", camera[0].view * light.get_position());
}

void Level::set_uniforms_camera()
{
	mat4 mv = (camera[0].view * camera[0].model);
	shader->setUniform("ModelViewMatrix", mv);
	shader->setUniform("NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	shader->setUniform("MVP", camera[0].projection * mv);
}

Shader* Level::get_shader()
{
	return shader;
}

Camera* Level::get_camera()
{
	return camera;
}

vector<Tile> Level::get_tiles()
{
	return this->tiles;
}

Light Level::get_light()
{
	return light;
}

void Level::set_light(Light l)
{
	light = l;
}