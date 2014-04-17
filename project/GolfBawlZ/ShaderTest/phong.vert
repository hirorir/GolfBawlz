#version 430

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

void main() {
	vec3 n = normalize(NormalMatrix * VertexNormal);
	vec4 vertInEyeCoords = ModelViewMatrix * vec4(VertexPosition,1.0);

	vec3 s = normalize(vec3(Light.Position - vertInEyeCoords));
	vec3 v = normalize(-vertInEyeCoords.xyz);
	vec3 r = reflect(-s, n);

	vec3 ambient = Light.La * Material.Ka;

	float sDotN = max(dot(s,n), 0.0);
	vec3 diffuse = Light.Ld * Material.Kd * sDotN;

	vec3 specular = vec3(0.0);
	if (sDotN > 0.0)
		specular = Light.Ls * Material.Ks * pow( max( dot(r,v), 0.0), Material.Shininess);

	// I = La*Ka + Ld*Kd*dot(s,n) + Ls*Ks*(dot(r, v))^f
	LightIntensity = ambient + diffuse + specular;

	gl_Position = MVP * vec4(VertexPosition,1.0);
}