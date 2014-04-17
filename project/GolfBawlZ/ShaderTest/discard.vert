#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;

out vec3 FrontColor;
out vec3 BackColor;
out vec2 TexCoord;

struct LightInfo {
	vec4 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};
uniform LightInfo Light;

struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};
uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void getEyeSpace(out vec3 norm, out vec4 position) {
	norm = normalize(NormalMatrix * VertexNormal);
	position = ModelViewMatrix * vec4(VertexPosition, 1.0);
}

vec3 phongModel(const vec3 norm, const vec4 position) {
	vec3 s = normalize(vec3(Light.Position - position));
	vec3 v = normalize(-position.xyz);
	vec3 r = reflect(-s, norm);

	vec3 ambient = Light.La * Material.Ka;

	float sDotN = max(dot(s, norm), 0.0);
	vec3 diffuse = Light.Ld * Material.Kd * sDotN;

	vec3 specular = vec3(0.0);
	if (sDotN > 0.0)
		specular = Light.Ls * Material.Ks * pow(max(dot(r,v), 0.0), Material.Shininess);

	return ambient + diffuse + specular;
}

void main() {
	vec3 normInEyeCoords;
	vec4 posInEyeCoords;
	TexCoord = VertexTexCoord;

	getEyeSpace(normInEyeCoords, posInEyeCoords);

	FrontColor = phongModel(normInEyeCoords, posInEyeCoords);
	BackColor = phongModel(-normInEyeCoords, posInEyeCoords);

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}