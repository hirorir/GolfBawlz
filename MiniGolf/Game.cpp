#include "Game.h"

Game::Game(int argc, char **argv)
{
	levels = Level::load_levels(argv[1]);
	current_level = 0;
	
	timer.start();
	current_time = 0;
}

Game::~Game()
{
	for (vector<Level*>::size_type i = 0; i < levels.size(); ++i) {
		delete levels[i];
	}
}

void Game::update()
{
	get_current_level()->update();

	Ball *ball = get_current_level()->get_ball();
	Ball *isect = get_current_level()->get_cup()->get_sphere();

	vec3 ball_pos = ball->get_position();
	vec3 sphere_pos = isect->get_position();

	float ball_rad = ball->get_radius();
	float sphere_rad = isect->get_radius();

	if (PhysicsObject::isect_sphere_sphere(ball_pos, ball_rad, sphere_pos, sphere_rad)) {
		next_level();
	}
}

void Game::draw()
{
	get_current_level()->draw();
}

void Game::resize(int w, int h){
	get_current_level()->get_camera()->resize(w, h);
}

Level *Game::get_current_level() const
{
	return levels.at(current_level);
}

void Game::next_level()
{
	if (current_level == levels.size() - 1) {
		current_level = 0;
	}
	else {
		current_level++;
	}
}

void Game::previous_level()
{
	if (current_level == 0) {
		current_level = levels.size() - 1;
	}
	else {
		current_level--;
	}
}

Timer Game::get_timer() const
{
	return timer;
}

double Game::get_current_time() const
{
	return  current_time;
}

void Game::set_current_time(double t)
{
	current_time = t;
}