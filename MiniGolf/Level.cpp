#include "Level.h"

Level::Level(vector<Tile> tiles, Ball b, Cup c)
{
	this->tiles = tiles;
	this->ball = b;
	this->cup = c;

	light = new Light(vec4(0.0f, 5.0f, 0.0f, 1.0f), vec3(0.5f), vec3(1.0f), vec3(1.0f));
}

void Level::update()
{
	// Run physics on ball and update ball position.
}

void Level::draw(Camera *camera)
{
	for (vector<Tile>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i].draw(camera, light);
	}

	ball.draw(camera, light);

	cup.draw(camera, light);
}

void Level::print()
{
	for (vector<Tile>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i].print();
	}

	cout << "BALL: "; ball.print();
	cout << "CUP: "; cup.print();
}

vector<Tile> Level::get_tiles()
{
	return this->tiles;
}

Light* Level::get_light()
{
	return light;
}

void Level::set_light(Light *l)
{
	light = l;
}

Ball Level::get_ball()
{
	return ball;
}