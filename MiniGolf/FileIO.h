#ifndef FILEIO_H
#define FILEIO_H

#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

#include "Level.h"
#include "Object3D.h"

using namespace std;

static const string TILE = "tile";
static const string TEE = "tee";
static const string CUP = "cup";

class FileIO
{
public:
	static Level load_level(string fname);
	static vector<string> string_split(const string &source, const char *delim = " ", bool keep_empty = false);
};

#endif