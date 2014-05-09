#include "Shader.h"

Shader::Shader(char *v, char *f) : program_handle(0)
{
	vertexShaderPath = v;
	fragmentShaderPath = f;
}

void Shader::getGLError()
{
	GLenum err = glGetError();
	while (err != GL_NO_ERROR) {
		printf("GLError %s set in File:%s Line:%d\n",
			getGLErrorString(err),
			__FILE__,
			__LINE__);
		err = glGetError();
	}
}

GLint Shader::checkCompileError(GLuint shader)
{
	GLint logLength, status;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		GLchar *log = (GLchar*)malloc(logLength);

		glGetShaderInfoLog(shader, logLength, &logLength, log);

		printf("Shader compile log:\n%s\n", log);
		free(log);
	}

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	return status;
}

const char* Shader::getGLErrorString(GLenum error)
{
	const char *str;
	switch (error) {
	case GL_NO_ERROR:
		str = "GL_NO_ERROR";
		break;
	case GL_INVALID_ENUM:
		str = "GL_INVALID_ENUM";
		break;
	case GL_INVALID_VALUE:
		str = "GL_INVALID_VALUE";
		break;
	case GL_INVALID_OPERATION:
		str = "GL_INVALID_OPERATION";
		break;
#if defined __gl_h_ || defined __gl3_h_
	case GL_OUT_OF_MEMORY:
		str = "GL_OUT_OF_MEMORY";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		str = "GL_INVALID_FRAMEBUFFER_OPERATION";
		break;
#endif
#if defined __gl_h_
	case GL_STACK_OVERFLOW:
		str = "GL_STACK_OVERFLOW";
		break;
	case GL_STACK_UNDERFLOW:
		str = "GL_STACK_UNDERFLOW";
		break;
	case GL_TABLE_TOO_LARGE:
		str = "GL_TABLE_TOO_LARGE";
		break;
#endif
	default:
		str = "(ERROR: Unknown Error Enum)";
		break;
	}
	return str;
}

void Shader::linkProgram()
{
	GLint logLength, status;

	glLinkProgram(program_handle);
	glGetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0) {
		GLchar *log = (GLchar*)malloc(logLength);
		glGetProgramInfoLog(program_handle, logLength, &logLength, log);
		printf("Program link log:\n%s\n", log);
		free(log);
	}

	glGetProgramiv(program_handle, GL_LINK_STATUS, &status);
	if (status == 0) {
		printf("Failed to link program");
		return;
	}

	glValidateProgram(program_handle);
	glGetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		GLchar *log = (GLchar*)malloc(logLength);
		glGetProgramInfoLog(program_handle, logLength, &logLength, log);
		printf("Program validate log:\n%s\n", log);
		free(log);
	}

	glGetProgramiv(program_handle, GL_VALIDATE_STATUS, &status);
	if (status == 0) {
		printf("Failed to validate program");
		return;
	}

	getGLError();
}

void Shader::buildProgram(sh *vtx, sh *frg)
{
	GLint status;
	GLchar *vtxSourceString = NULL, *frgSourceString = NULL;
	float  glLanguageVersion;

	sscanf_s((char *)glGetString(GL_SHADING_LANGUAGE_VERSION), "%f", &glLanguageVersion);

	GLuint version = static_cast<GLuint>(100 * glLanguageVersion);
	const GLsizei versionStringSize = sizeof("#version 123\n");

	program_handle = glCreateProgram();

	vtxSourceString = (char*)malloc(vtx->byteSize + versionStringSize);
	frgSourceString = (char*)malloc(frg->byteSize + versionStringSize);

	sprintf(vtxSourceString, "#version %d\n%s", version, vtx->string);
	sprintf(frgSourceString, "#version %d\n%s", version, frg->string);

	GLuint vtxShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vtxShader, 1, (const GLchar **)&(vtxSourceString), NULL);

	glCompileShader(vtxShader);
	status = checkCompileError(vtxShader);
	if (status == 0) {
		printf("Failed to compile vtx shader:\n%s\n", vtxSourceString);
		return;
	}

	GLuint frgShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frgShader, 1, (const GLchar **)&(frgSourceString), NULL);

	glCompileShader(frgShader);
	status = checkCompileError(frgShader);
	if (status == 0) {
		printf("Failed to compile frg shader:\n%s\n", frgSourceString);
		return;
	}

	free(vtxSourceString);
	vtxSourceString = NULL;

	free(frgSourceString);
	frgSourceString = NULL;

	glAttachShader(program_handle, vtxShader);
	glDeleteShader(vtxShader);

	glAttachShader(program_handle, frgShader);
	glDeleteShader(frgShader);

	linkProgram();
}

void Shader::buildShaderInfo(sh *source, const char *filepathname)
{
	const char* suffixBegin = filepathname + strlen(filepathname) - 4;

	if (strncmp(suffixBegin, ".fsh", 4) == 0) {
		source->shaderType = GL_FRAGMENT_SHADER;
	}
	else if (strncmp(suffixBegin, ".vsh", 4) == 0) {
		source->shaderType = GL_VERTEX_SHADER;
	}
	else {
		source->shaderType = 0;
	}

	FILE* curFile = fopen(filepathname, "rb");

	// Get the size of the source
	fseek(curFile, 0, SEEK_END);
	GLsizei fileSize = (GLsizei)ftell(curFile);

	// Add 1 to the file size to include the null terminator for the string
	source->byteSize = fileSize + 1;

	// Alloc memory for the string
	source->string = (char*)malloc(source->byteSize);

	// Read entire file into the string from beginning of the file
	fseek(curFile, 0, SEEK_SET);
	fread(source->string, 1, fileSize, curFile);

	fclose(curFile);

	// Insert null terminator
	source->string[fileSize] = 0;
}

void Shader::readAndCompileShader()
{
	sh *vtxSource = (sh*)calloc(sizeof(sh), 1);
	sh *frgSource = (sh*)calloc(sizeof(sh), 1);

	buildShaderInfo(vtxSource, vertexShaderPath);
	buildShaderInfo(frgSource, fragmentShaderPath);

	buildProgram(vtxSource, frgSource);

	free(vtxSource);
	vtxSource = NULL;

	free(frgSource);
	frgSource = NULL;
}

void Shader::use()
{
	if (program_handle <= 0) {
		printf("[ERROR] Program Handle: %d", program_handle);
		return;
	}
	glUseProgram(program_handle);
	glBindVertexArray(0);
}

GLuint Shader::getProgramHandle()
{
	return program_handle;
}

void Shader::bindAttribLocation(GLuint location, const char *name)
{
	glBindAttribLocation(program_handle, location, name);
}

void Shader::bindFragDataLocation(GLuint location, const char *name)
{
	glBindFragDataLocation(program_handle, location, name);
}

void Shader::setUniform(const char *name, float x, float y)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform2f(loc, x, y);
	}
}

void Shader::setUniform(const char *name, float x, float y, float z)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform3f(loc, x, y, z);
	}
}

void Shader::setUniform(const char *name, const vec3 &v)
{
	this->setUniform(name, v.x, v.y, v.z);
}

void Shader::setUniform(const char *name, const vec4 &v)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform4f(loc, v.x, v.y, v.z, v.w);
	}
}

void Shader::setUniform(const char *name, const mat4 &m)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
	}
}

void Shader::setUniform(const char *name, const mat3 &m)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
	}
}

void Shader::setUniform(const char *name, float val)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform1f(loc, val);
	}
}

void Shader::setUniform(const char *name, int val)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform1i(loc, val);
	}
}

void Shader::setUniform(const char *name, bool val)
{
	int loc = getUniformLocation(name);
	if (loc >= 0) {
		glUniform1i(loc, val);
	}
}

void Shader::printActiveUniforms()
{
	GLint nUniforms, size, location, maxLen;
	GLchar * name;
	GLsizei written;
	GLenum type;

	glGetProgramiv(program_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv(program_handle, GL_ACTIVE_UNIFORMS, &nUniforms);

	name = (GLchar *)malloc(maxLen);

	printf(" Location | Name\n");
	printf("------------------------------------------------\n");
	for (int i = 0; i < nUniforms; ++i) {
		glGetActiveUniform(program_handle, i, maxLen, &written, &size, &type, name);
		location = glGetUniformLocation(program_handle, name);
		printf(" %-8d | %s\n", location, name);
	}

	free(name);
}

void Shader::printActiveAttribs()
{

	GLint written, size, location, maxLength, nAttribs;
	GLenum type;
	GLchar * name;

	glGetProgramiv(program_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
	glGetProgramiv(program_handle, GL_ACTIVE_ATTRIBUTES, &nAttribs);

	name = (GLchar *)malloc(maxLength);

	printf(" Index | Name\n");
	printf("------------------------------------------------\n");
	for (int i = 0; i < nAttribs; i++) {
		glGetActiveAttrib(program_handle, i, maxLength, &written, &size, &type, name);
		location = glGetAttribLocation(program_handle, name);
		printf(" %-5d | %s\n", location, name);
	}

	free(name);
}

int Shader::getUniformLocation(const char *name)
{
	return glGetUniformLocation(program_handle, name);
}

void Shader::set_uniforms_camera(Shader *shader, Camera *camera, mat4 model)
{
	mat4 mv = (camera->get_view() * model);
	shader->setUniform("ModelViewMatrix", mv);
	shader->setUniform("NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	shader->setUniform("MVP", camera->get_projection() * mv);
}

void Shader::set_uniforms_light(Shader *shader, Camera *camera, Light *light)
{
	shader->setUniform("Light.La", light->get_ambient());
	shader->setUniform("Light.Ld", light->get_diffuse());
	shader->setUniform("Light.Ls", light->get_specular());
	shader->setUniform("Light.Position", camera->get_view() * light->get_position());
}

void Shader::set_uniforms_material(Shader *shader, Material mat)
{
	shader->setUniform("Material.Ka", mat.get_ambient());
	shader->setUniform("Material.Kd", mat.get_diffuse());
	shader->setUniform("Material.Ks", mat.get_specular());
	shader->setUniform("Material.Shininess", mat.get_shininess());
}

void Shader::new_shader(char *vtxPath, char *frgPath)
{
	program_handle = 0;
	vertexShaderPath = vtxPath;
	fragmentShaderPath = frgPath;
	this->readAndCompileShader();
}