#include <GL\glew.h>
#include <GL\freeglut.h>
#include <gl\gl.h>
#include <gl\GLU.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;
using namespace glm;

#define PI 3.141592653589793
#define TWOPI 6.2831853071795862
#define TO_RADIANS(x) (x * 0.017453292519943295)
#define TO_DEGREES(x) (x * 57.29577951308232)

void checkGlErrors();
void readAndCompileShader(GLuint programHandle, const char *vertexShaderFileName, const char *fragmentShaderFileName);
void readAndCompileSingleShader(GLuint shaderHandle, const char* shaderFileName);

void setUniform(GLuint programHandle, const char *name, float x, float y, float z);
void setUniform(GLuint programHandle, const char *name, const vec4 & v);
void setUniform(GLuint programHandle, const char *name, const mat4 & m);
void setUniform(GLuint programHandle, const char *name, const mat3 & m);
void setUniform(GLuint programHandle, const char *name, float val);

static int checkForOpenGLError(const char *, int);
static void dumpGLInfo(bool dumpExtensions = false);

class Noncopyable {
protected:
	Noncopyable() {}
	~Noncopyable() {}
private:
	Noncopyable(const Noncopyable&);
	const Noncopyable& operator= (const Noncopyable&);
};

class GlShader : Noncopyable {
	GLuint handle;

public:
	GlShader(GLenum shaderType) {
		handle = glCreateShader(shaderType); // create shader handle
		if (handle == 0)
			throw std::runtime_error("glCreateShader fails");
		checkGlErrors();
	}

	~GlShader() {
		glDeleteShader(handle);
	}

	operator GLuint() const {
		return handle;
	}
};

class GlProgram : Noncopyable {
	GLuint handle;

public:
	GlProgram() {
		handle = glCreateProgram();
		if (handle == 0)
			throw std::runtime_error("glCreateProgram fails");
		checkGlErrors();
	}

	~GlProgram() {
		glDeleteProgram(handle);
	}

	// Casts to GLuint so can be used directly by glUseProgram and so on
	operator GLuint() const {
		return handle;
	}
};

class GlTexture : Noncopyable {
	GLuint handle;

public:
	GlTexture() {
		glGenTextures(1, &handle);
		checkGlErrors();
	}

	~GlTexture() {
		glDeleteTextures(1, &handle);
	}

	// Casts to GLuint so can be used directly by glBindTexture and so on
	operator GLuint () const {
		return handle;
	}
};

class GlBufferObject : Noncopyable {
	GLuint handle;

public:
	GlBufferObject() {
		glGenBuffers(1, &handle);
		checkGlErrors();
	}

	~GlBufferObject() {
		glDeleteBuffers(1, &handle);
	}

	// Casts to GLuint so can be used directly glBindBuffer and so on
	operator GLuint() const {
		return handle;
	}
};

void checkGlErrors() {
	const GLenum errCode = glGetError();

	if (errCode != GL_NO_ERROR) {
		string error("GL Error: ");
		error += reinterpret_cast<const char*>(gluErrorString(errCode));
		cerr << error << endl;
		throw runtime_error(error);
	}
}

static void readTextFile(const char *fn, vector<char>& data) {
	// Sets ios::binary bit to prevent end of line translation, so that the
	// number of bytes we read equals file size
	ifstream ifs(fn, ios::in | ios::binary);

	// Sets bits to report IO error using exception
	ifs.exceptions(ios::eofbit | ios::failbit | ios::badbit);
	ifs.seekg(0, ios::end);
	size_t len = ifs.tellg();

	data.resize(len);

	ifs.seekg(0, ios::beg);
	ifs.read(&data[0], len);
}

static void printInfoLog(GLuint obj, const string& filename) {
	GLint infologLength = 0;
	GLint charsWritten = 0;
	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);
	if (infologLength > 0) {
		string infoLog(infologLength, ' ');
		glGetInfoLogARB(obj, infologLength, &charsWritten, &infoLog[0]);
		std::cerr << "##### Log [" << filename << "]:\n" << infoLog << endl;
	}
}

void readAndCompileSingleShader(GLuint shaderHandle, const char *fn) {
	vector<char> source;
	readTextFile(fn, source);

	const char *ptrs[] = { &source[0] };
	const GLint lens[] = { source.size() };
	glShaderSource(shaderHandle, 1, ptrs, lens);   // load the shader sources

	glCompileShader(shaderHandle);

	printInfoLog(shaderHandle, fn);

	GLint compiled = 0;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
		throw runtime_error("fails to compile GL shader");
}

void readAndCompileShader(GLuint programHandle, const char * vertexShaderFileName, const char * fragmentShaderFileName) {
	GlShader vs(GL_VERTEX_SHADER);
	GlShader fs(GL_FRAGMENT_SHADER);

	readAndCompileSingleShader(vs, vertexShaderFileName);
	readAndCompileSingleShader(fs, fragmentShaderFileName);

	glAttachShader(programHandle, vs);
	glAttachShader(programHandle, fs);

	glLinkProgram(programHandle);

	glDetachShader(programHandle, vs);
	glDetachShader(programHandle, fs);

	GLint linked = 0;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);
	printInfoLog(programHandle, "linking");

	if (!linked)
		throw runtime_error("fails to link shaders");
}

void setUniform(GLuint programHandle, const char *name, float x, float y, float z) {
	int loc = glGetUniformLocation(programHandle, name);

	if (loc >= 0) {
		glUniform3f(loc, x, y, z);
	}
}

void setUniform(GLuint programHandle, const char *name, const vec4 & v) {
	int loc = glGetUniformLocation(programHandle, name);

	if (loc >= 0) {
		glUniform4f(loc, v.x, v.y, v.z, v.w);
	}
}

void setUniform(GLuint programHandle, const char *name, float val) {
	int loc = glGetUniformLocation(programHandle, name);
	if (loc >= 0)
	{
		glUniform1f(loc, val);
	}
}

void setUniform(GLuint programHandle, const char *name, const mat4 & m) {
	int loc = glGetUniformLocation(programHandle, name);

	if (loc >= 0) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
	}
}

void setUniform(GLuint programHandle, const char *name, const mat3 & m) {
	int loc = glGetUniformLocation(programHandle, name);

	if (loc >= 0) {
		glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
	}
}

int checkForOpenGLError(const char * file, int line) {
	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
		retCode = 1;
		glErr = glGetError();
	}
	return retCode;

}

void dumpGLInfo(bool dumpExtensions) {
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	printf("GL Vendor    : %s\n", vendor);
	printf("GL Renderer  : %s\n", renderer);
	printf("GL Version   : %s\n", version);
	printf("GL Version   : %d.%d\n", major, minor);
	printf("GLSL Version : %s\n", glslVersion);

	if (dumpExtensions) {
		GLint nExtensions;
		glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
		for (int i = 0; i < nExtensions; i++) {
			printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
		}
	}
}

class VBOTorus {
private:
	unsigned int vaoHandle;
	int faces, rings, sides;

	void generateVerts(float *, float *, float *, unsigned int *, float, float);

public:
	VBOTorus(float, float, int, int);

	void render() const;
};

VBOTorus::VBOTorus(float outerRadius, float innerRadius, int nsides, int nrings) : rings(nrings), sides(nsides) {
	faces = sides * rings;
	int nVerts = sides * (rings + 1);   // One extra ring to duplicate first ring

	// Verts
	float * v = new float[3 * nVerts];
	// Normals
	float * n = new float[3 * nVerts];
	// Tex coords
	float * tex = new float[2 * nVerts];
	// Elements
	unsigned int * el = new unsigned int[6 * faces];

	// Generate the vertex data
	generateVerts(v, n, tex, el, outerRadius, innerRadius);

	// Create and populate the buffer objects
	unsigned int handle[4];
	glGenBuffers(4, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), v, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), n, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ARRAY_BUFFER, (2 * nVerts) * sizeof(float), tex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * faces * sizeof(unsigned int), el, GL_STATIC_DRAW);

	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;

	// Create the VAO
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);  // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));

	glEnableVertexAttribArray(1);  // Vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glEnableVertexAttribArray(2);  // Texture coords
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);

	glBindVertexArray(0);
}

void VBOTorus::render() const {
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_TRIANGLES, 6 * faces, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}

void VBOTorus::generateVerts(float * verts, float * norms, float * tex, unsigned int * el, float outerRadius, float innerRadius) {
	float ringFactor = (float)(TWOPI / rings);
	float sideFactor = (float)(TWOPI / sides);
	int idx = 0, tidx = 0;
	for (int ring = 0; ring <= rings; ring++) {
		float u = ring * ringFactor;
		float cu = cos(u);
		float su = sin(u);
		for (int side = 0; side < sides; side++) {
			float v = side * sideFactor;
			float cv = cos(v);
			float sv = sin(v);
			float r = (outerRadius + innerRadius * cv);
			verts[idx] = r * cu;
			verts[idx + 1] = r * su;
			verts[idx + 2] = innerRadius * sv;
			norms[idx] = cv * cu * r;
			norms[idx + 1] = cv * su * r;
			norms[idx + 2] = sv * r;
			tex[tidx] = (float)(u / TWOPI);
			tex[tidx + 1] = (float)(v / TWOPI);
			tidx += 2;
			// Normalize
			float len = std::sqrt(norms[idx] * norms[idx] +
				norms[idx + 1] * norms[idx + 1] +
				norms[idx + 2] * norms[idx + 2]);
			norms[idx] /= len;
			norms[idx + 1] /= len;
			norms[idx + 2] /= len;
			idx += 3;
		}
	}

	idx = 0;
	for (int ring = 0; ring < rings; ring++) {
		int ringStart = ring * sides;
		int nextRingStart = (ring + 1) * sides;
		for (int side = 0; side < sides; side++) {
			int nextSide = (side + 1) % sides;
			// The quad
			el[idx] = (ringStart + side);
			el[idx + 1] = (nextRingStart + side);
			el[idx + 2] = (nextRingStart + nextSide);
			el[idx + 3] = ringStart + side;
			el[idx + 4] = nextRingStart + nextSide;
			el[idx + 5] = (ringStart + nextSide);
			idx += 6;
		}
	}
}

// Globals.
mat4 model;
mat4 view;
mat4 projection;

GLuint program;
VBOTorus *torus;

void initProgram() {
	program = glCreateProgram();
	readAndCompileShader(program, "shaders\\diffuse.vert", "shaders\\diffuse.frag");
	glUseProgram(program);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	torus = new VBOTorus(0.7f, 0.3f, 50, 50);

	model = mat4(1.0f);
	model *= rotate(-35.0f, vec3(1.0f, 0.0f, 0.0f));
	model *= rotate(35.0f, vec3(0.0f, 1.0f, 0.0f));
	view = lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = mat4(1.0f);

	setUniform(program, "Kd", 0.9f, 0.5f, 0.3f);
	setUniform(program, "Ld", 1.0f, 1.0f, 1.0f);
	setUniform(program, "LightPosition", view * vec4(5.0f, 5.0f, 2.0f, 1.0f));
}

void setMatrices() 
{
	mat4 mv = view * model;
	setUniform(program, "ModelViewMatrix", mv);
	setUniform(program, "NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	setUniform(program, "MVP", projection * mv);
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setMatrices();
	torus->render();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) 
{
	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void reshape(int w, int h) 
{
	glViewport(0, 0, w, h);
	projection = perspective(70.0f, (float)w / h, 0.3f, 100.0f);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Golf BawlZ");
	glewInit();

	initProgram();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	glutMainLoop();

	return 0;
}