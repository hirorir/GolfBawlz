#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>

#include "Level.h"

using namespace std;

class FileIO
{
public:
	// Constructor.
	explicit FileIO();

	// Destructor.
	~FileIO();
	
	static Level load_level(string fname);
};

#endif