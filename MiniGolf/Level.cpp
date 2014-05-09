#include "Level.h"
#include "Physics.h"
#include "Intersect.h"

Level::Level(vector<Tile*> tiles, Ball *b, Cup *c)
{
	this->tiles = tiles;
	this->ball = b;
	this->cup = c;

	light = new Light(vec4(0.0f, 5.0f, 0.0f, 1.0f), vec3(0.5f), vec3(1.0f), vec3(1.0f));
}

Level::~Level()
{
	for (vector<Tile*>::size_type i = 0; i < tiles.size(); ++i) {
		delete tiles[i];
	}
	delete light;
	delete ball;
	delete cup;
}

void Level::update()
{
	//all of these should be part of the ball's update function
	ball->applyForce(physics::gravity);
	for (int i = 0; i < tiles.size(); i++){
		if (Intersect::isect_sphere_plane(ball->get_position(), ball->get_radius, ball->get_velocity(), tiles[i]->get_normal(), tiles[i]->get_vertices())){
			ball->applyForce(-physics::gravity);
			cout << "BOOM IT COLLIDED AT (" << ball->get_position().x << ", " << ball->get_position().y << ", " << ball->get_position().z << ")" << endl;
			break;
		}
	}
	ball->set_position(ball->get_velocity());
	//cout << "POSITION: " << "(" << ball->get_position().x << ", " << ball->get_position().y << ", " << ball->get_position().z << ")" << endl;
	//cout << "VELOCITY: " << "(" << ball->get_velocity().x << ", " << ball->get_velocity().y << ", " << ball->get_velocity().z << ")" << endl;
	// Run physics on ball and update ball position.
}

void Level::draw(Camera *camera)
{
	for (vector<Tile*>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i]->draw(camera, light);
	}

	ball->draw(camera, light);

	cup->draw(camera, light);
}

void Level::print()
{
	for (vector<Tile*>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i]->print();
	}

	cout << "BALL: "; ball->print();
	cout << "CUP: "; cup->print();
}

vector<Tile*> Level::get_tiles()
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

Ball *Level::get_ball()
{
	return ball;
}

Tile *Level::get_tile_by_id(int id)
{
	for (vector<Tile*>::size_type i = 0; i < tiles.size(); ++i) {
		if (tiles[i]->get_tile_id() == id) {
			return tiles[i];
		}
	}
	return NULL;
}