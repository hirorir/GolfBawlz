#include "Level.h"

Level::Level(vector<Tile> tiles, Tee tee, Cup cup)
{
	this->tiles = tiles;
	this->tee = tee;
	this->cup = cup;

	print();
	tee.print();
	cup.print();
}

void Level::draw()
{
	for (vector<Tile>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i].draw();
	}

	// TO DO: Draw cup, tee, and border.
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