#include "GUI.h"

GUI::GUI(string path){
	loadTexture(path);
}

// Routine to draw a stroke character string.
void writeStrokeString(void *font, const char *string)
{
	const char *c;
	for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

void GUI::draw(string course, string level, string par, string angle, string power){
	glUseProgram(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);

	glColor4f(1, 1, 1, 1);

	glPushMatrix();
	glTranslatef(20.0, 950.0, 0.0);
	glScalef(0.2, 0.2, 1.0);
	string course_name = "Course: " + course;
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, course_name.c_str());
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.0, 900.0, 0.0);
	glScalef(0.2, 0.2, 1.0);
	string level_name = "Level: " + level;
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, level_name.c_str());
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.0, 850.0, 0.0);
	glScalef(0.2, 0.2, 1.0);
	string p = "Par: " + par;
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, p.c_str());
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1200.0, 50.0, 0.0);
	glScalef(0.2, 0.2, 1.0);
	string pr = "Power: " + power;
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, pr.c_str());
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1200.0, 80.0, 0.0);
	glScalef(0.2, 0.2, 1.0);
	string a = "Angle: " + angle;
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, a.c_str());
	glPopMatrix();

	glTranslatef(20.0f, 20.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 100, 0);
	glTexCoord2f(1, 1); glVertex3f(100, 100, 0);
	glTexCoord2f(1, 0); glVertex3f(100, 0, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void GUI::loadTexture(string path){
	texture = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (!texture){
		cout << "Invalid path " << path << endl;
	}
	else{
		cout << path << " loaded" << endl;
	}
}