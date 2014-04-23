#include "FileIO.h"

Level FileIO::load_level(string fname)
{
	vector<Tile> tiles;
	Tee tee;
	Cup cup;

	ifstream in_file(fname);

	if (in_file.is_open()) {

		string line;
		while (getline(in_file, line)) {
			vector<string> tokens = FileIO::string_split(line);

			transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower);

			if (!tokens[0].compare(TILE)) {
				int tile_id = atoi(tokens[1].c_str());
				int edge_count = atoi(tokens[2].c_str());

				vector<int> neighbors;
				for (vector<int>::size_type i = tokens.size() - edge_count; i < tokens.size(); ++i) {
					neighbors.push_back(atoi(tokens[i].c_str()));
				}

				vector<float> verticies;
				for (vector<float>::size_type i = 3; i < tokens.size() - edge_count; ++i) {
					verticies.push_back((float) atof(tokens[i].c_str()));
				}

				tiles.push_back(Tile(tile_id, verticies.size(), edge_count, verticies, neighbors));
			}
			else if (!tokens[0].compare(TEE)) {
				tee.set_tile_id(atoi(tokens[1].c_str()));
				
				vector<float> positions;
				for (int i = 2; i < 5; ++i) {
					positions.push_back((float) atof(tokens[i].c_str()));
				}
				tee.set_position(positions);
			}
			else if (!tokens[0].compare(CUP)) {
				cup.set_tile_id(atoi(tokens[1].c_str()));

				vector<float> positions;
				for (int i = 2; i < 5; ++i) {
					positions.push_back((float) atof(tokens[i].c_str()));
				}
				cup.set_position(positions);
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

	return Level(tiles, tee, cup);
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