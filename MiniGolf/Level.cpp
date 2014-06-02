#include "Level.h"

Level::Level(vector<Tile*> tiles, Ball *b, Cup *c, Tee *tee, string course_name, string level_name, int par)
{
	this->tiles = tiles;
	camera = new Camera();
	light = new Light(vec4(0.0f, 5.0f, 0.0f, 1.0f), vec3(0.5f), vec3(1.0f), vec3(1.0f));
	this->ball = b;
	this->cup = c;
	this->tee = tee;
	this->par = par;
	this->course_name = course_name;
	this->level_name = level_name;
}

Level::~Level()
{
	for (vector<Tile*>::size_type i = 0; i < tiles.size(); ++i) {
		delete tiles[i];
	}
	delete camera;
	delete light;
	delete ball;
	delete cup;
}

void Level::update()
{
}

void Level::draw()
{
	for (vector<Tile*>::size_type i = 0; i < tiles.size(); ++i) {
		tiles[i]->draw(camera, light);
	}

	ball->draw(camera, light);

	cup->draw(camera, light);

	tee->draw(camera, light);
}

Camera *Level::get_camera() const
{
	return camera;
}

Ball *Level::get_ball() const
{
	return ball;
}

string Level::get_course_name() const
{
	return course_name;
}

string Level::get_level_name() const
{
	return level_name;
}

int Level::get_par() const
{
	return par;
}

vector<Tile*> Level::get_tiles() const
{
	return tiles;
}

void Level::print() const
{
	cout << "Course this Level belongs to: " << course_name << endl;
	cout << "Level name: " << level_name << endl;
	cout << "Par: " << par << endl;
	cout << "Tile Vertices: " << endl;
	for (vector<Tile*>::size_type i = 0; i < tiles.size(); ++i) {
		tiles.at(i)->print();
	}
	light->print();
}

vector<string> string_split(const string &source, const char *delim, bool keep_empty)
{
	vector<string> tokens;

	size_t prev = 0, next = 0;

	while ((next = source.find_first_of(delim, prev)) != string::npos) {
		if (keep_empty || (next - prev != 0)) {
			tokens.push_back(source.substr(prev, next - prev));
		}
		prev = ++next;
	}

	if (prev < source.size()) {
		tokens.push_back(source.substr(prev));
	}

	return tokens;
}

vector<Level*> Level::load_levels(string fname)
{
	vector<Level*> levels;
	string course_name;
	int number_of_holes;

	ifstream in_file(fname);
	if (in_file.is_open()) {

		string line;
			getline(in_file, line);
			vector<string> tokens = string_split(line, " ", false); // Split up tokens by spaces.

			if (!tokens[0].compare(COURSE)) {
				course_name = "";
				for (vector<string>::size_type i = 1; i < tokens.size() - 1; ++i) {
					course_name += tokens[i] + " ";
				}
				number_of_holes = atoi(tokens[tokens.size() - 1].c_str());
				
				for (int i = 0; i < number_of_holes; ++i) {
					vector<Tile*> tiles;
					Ball *ball;
					Cup *cup;
					Tee *tee;
					string level_name;
					int par;
					float positions[3];

					getline(in_file, line);
					vector<string> tokens = string_split(line, " ", false); // Split up tokens by spaces.

					if (!tokens[0].compare(BEGIN_HOLE)) {
						while (true) {
							getline(in_file, line);
							vector<string> tokens = string_split(line, " ", false); // Split up tokens by spaces.

							if (!tokens[0].compare(NAME)) {
								level_name = "";
								for (vector<string>::size_type i = 1; i < tokens.size(); ++i) {
									level_name += tokens[i] + " ";
								}
							}
							else if (!tokens[0].compare(PAR)) {
								par = atoi(tokens[1].c_str());
							}
							else if (!tokens[0].compare(TILE)) {
								int tile_id = atoi(tokens[1].c_str());
								int edge_count = atoi(tokens[2].c_str());

								vector<int> neighbors;
								for (vector<int>::size_type i = tokens.size() - edge_count; i < tokens.size(); ++i) {
									neighbors.push_back(atoi(tokens[i].c_str()));
								}

								vector<vec3> vertices;
								vec3 v;
								for (vector<float>::size_type i = 3; i < tokens.size() - edge_count; i += 3) {
									v.x = (float) atof(tokens[i].c_str());
									v.y = (float) atof(tokens[i + 1].c_str());
									v.z = (float) atof(tokens[i + 2].c_str());
									vertices.push_back(v);
								}

								tiles.push_back(new Tile(tile_id, edge_count, vertices, neighbors));
							}
							else if (!tokens[0].compare(TEE)) {
								int tile_id = atoi(tokens[1].c_str());

								for (int i = 2; i < 5; ++i) {
									positions[i - 2] = (float)atof(tokens[i].c_str());
								}

								vec3 pos = vec3(positions[0], positions[1], positions[2]);
			
								ball = new Ball(tile_id, pos);

								vector<vec3> verts;
								verts.push_back(vec3(pos.x - 0.09, pos.y + 0.01, pos.z - 0.09));
								verts.push_back(vec3(pos.x + 0.09, pos.y + 0.01, pos.z - 0.09));
								verts.push_back(vec3(pos.x + 0.09, pos.y + 0.01, pos.z + 0.09));
								verts.push_back(vec3(pos.x - 0.09, pos.y + 0.01, pos.z + 0.09));

								tee = new Tee(tile_id, pos, verts);
							}
							else if (!tokens[0].compare(CUP)) {
								int tile_id = atoi(tokens[1].c_str());

								for (int i = 2; i < 5; ++i) {
									positions[i - 2] = (float)atof(tokens[i].c_str());
								}

								cup = new Cup(tile_id, vec3(positions[0], positions[1], positions[2]));
							}
							else if (!tokens[0].compare(END_HOLE)) {
								break;
							}
							else {
								cout << "error - unable to identify first token." << endl;
							}
						}
						levels.push_back(new Level(tiles, ball, cup, tee, course_name, level_name, par));
					}
				}
			}
	}
	else {
		cout << "error - unable to open in_file." << endl;
	}

	in_file.close();

	return levels;
}