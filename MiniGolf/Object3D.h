#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <iostream>
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

using namespace std;

class Object3D
{
public:
	Object3D();
	Object3D(vector<float> position, int tile_id);

	virtual void init_gl() = 0;
	virtual void draw() = 0;

	void print();

	GLuint get_vao_handle();

	int get_tile_id();
	void set_tile_id(int id);

	vector<float> get_position();
	void set_position(vector<float> position);

private:
	GLuint vao_handle;
	int tile_id;
	vector<float> position;
};

#endif