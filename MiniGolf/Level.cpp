#include "Level.h"

Level::Level(vector<Tile> tiles, Tee tee, Cup cup)
{
	this->tiles = tiles;
	this->tee = tee;
	this->cup = cup;
	this->light = Light(vec4(0.0, 10.0, 0.0, 1.0), vec3(0.4f), vec3(1.0f), vec3(1.0f));

	print();
	cout << "TEE: "; tee.print();
	cout << "CUP: "; cup.print();
}

void Level::draw()
{
	for (vector<Tile>::size_type i = 0; i < tiles.size(); ++i) {
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

Tile Level::get_tile_at(int i) 
{
	return tiles[i];
}