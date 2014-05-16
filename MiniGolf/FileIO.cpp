#include "FileIO.h"

/*
load_level(string fname): Load level from file.
*/
Level *FileIO::load_level(string fname)
{
	vector<Tile*> tiles; // List of tiles in level.
	Cup *cup; // Level's cup.
	Ball *ball; // Level's ball.

	char *init_vtx_path = "shaders/ads.vert"; // Initial vertex shader path.
	char *init_frg_path = "shaders/ads.frag"; // Initial fragment shader path.

	int tile_id; // Temp tile_id for each tile.

	float positions[3]; // Temp position for tee and cup.

	ifstream in_file(fname); // Open level file.

	if (in_file.is_open()) { // If the file opened successfully.

		string line; // Holds a line in the file.

		while (!in_file.eof()) {
			getline(in_file, line); // Get a line.

			vector<string> tokens = FileIO::string_split(line); // Split the line into individual tokens.

			transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower); // Turn each token to lower-case.
			
			if (!tokens[0].compare(TILE)) { // It the first token is 'tile.'
				int tile_id = atoi(tokens[1].c_str()); // Store the tile_id.
				int edge_count = atoi(tokens[2].c_str()); // Store the edge_count.

				vector<int> neighbors; // Temp for the tiles neighbors.
				for (vector<int>::size_type i = tokens.size() - edge_count; i < tokens.size(); ++i) { // Loop through starting 'neighbors' portion of the line.
					neighbors.push_back(atoi(tokens[i].c_str())); // Store the neighbors.
				}

				vector<float> vertices; // Temp for the tiles vertices.
				for (vector<float>::size_type i = 3; i < tokens.size() - edge_count; ++i) {
					vertices.push_back((float)atof(tokens[i].c_str()));
				}

				tiles.push_back(new Tile(tile_id, edge_count, vertices, neighbors, init_vtx_path, init_frg_path));
			}
			else if (!tokens[0].compare(TEE)) {
				tile_id = atoi(tokens[1].c_str());
				
				for (int i = 2; i < 5; ++i) {
					positions[i-2] = (float) atof(tokens[i].c_str());
				}

				ball = new Ball(tile_id, vec3(positions[0], positions[1], positions[2]), init_vtx_path, init_frg_path);
			}
			else if (!tokens[0].compare(CUP)) {
				tile_id = atoi(tokens[1].c_str());

				for (int i = 2; i < 5; ++i) {
					positions[i - 2] = (float)atof(tokens[i].c_str());
				}

				cup = new Cup(tile_id, vec3(positions[0], positions[1], positions[2]), init_vtx_path, init_frg_path);
			}
			else {
				cout << "error - unable to identify first token." << endl;
			}
		}
	}
	else {
		cout << "error - unable to open in_file." << endl;
	}

	in_file.close();

	return new Level(tiles, ball, cup);
}

vector<string> FileIO::string_split(const string &source, const char *delim, bool keep_empty)
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