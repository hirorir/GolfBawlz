#version 430

subroutine vec3 shadeModelType(vec3 normal, vec4 position);
subroutine uniform shadeModelType shadeModel;

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

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

subroutine(shadeModelType) vec3 phongModel(const vec3 norm, const vec4 position) {
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

subroutine(shadeModelType) vec3 diffuseOnly(vec3 norm, vec4 position) {
	vec3 s = normalize(vec3(Light.Position - position));
	return Light.Ld * Material.Kd * max(dot(s,norm), 0.0);
}

void main() {
	vec3 normInEyeCoords;
	vec4 vertInEyeCoords;

	getEyeSpace(normInEyeCoords, vertInEyeCoords);
	LightIntensity = shadeModel(normInEyeCoords, vertInEyeCoords);

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}