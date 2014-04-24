#include "Level.h"

Level::Level(vector<Tile> tiles, Tee tee, Cup cup)
{
	this->tiles = tiles;
	this->tee = tee;
	this->cup = cup;
	this->light = Light(vec4(0.0f, 5.0f, 0.0f, 1.0f), vec3(0.5f), vec3(1.0f), vec3(1.0f));

	shader = new Shader("shaders/phong.vert", "shaders/phong.frag");
	shader->readAndCompileShader();

	camera = new Camera();

	print();
	cout << "TEE: "; tee.print();
	cout << "CUP: "; cup.print();
}

void Level::draw()
{
	shader->use();
	set_uniforms_light();
	set_uniforms_camera();

	for (vector<Tile>::size_type i = 0; i < tiles.size(); ++i) {
		set_uniforms_tile(tiles[i]);
		tiles[i].draw();
	}

	tee.draw();
	cup.draw();
}

void Level::print()
{
	for (vector<Tile>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i].print();
	}
}

void Level::set_uniforms_tile(Tile tile)
{
	shader->setUniform("Material.Ka", tile.get_material().get_ambient());
	shader->setUniform("Material.Kd", tile.get_material().get_diffuse());
	shader->setUniform("Material.Ks", tile.get_material().get_specular());
	shader->setUniform("Material.Shininess", tile.get_material().get_shininess());
}

void Level::set_uniforms_light()
{
	shader->setUniform("Light.La", 0.4f, 0.4f, 0.4f);
	shader->setUniform("Light.Ld", light.get_diffuse());
	shader->setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
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

Tee Level::get_tee()
{
	return tee;
}

Cup Level::get_cup()
{
	return cup;
}

Light Level::get_light()
{
	return light;
}

void Level::set_light(Light l)
{
	light = l;
}