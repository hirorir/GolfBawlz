#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightPosition; // Light position in eye coords.
uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main() {
    vec3 n = normalize( NormalMatrix * VertexNormal);
    vec4 vertInEyeCoords = ModelViewMatrix * vec4(VertexPosition,1.0);
    vec3 s = normalize(vec3(LightPosition - vertInEyeCoords));

	// I = Ld*Kd*dot(n,s)
    LightIntensity = Ld * Kd * max( dot( s, n ), 0.0 );

    gl_Position = MVP * vec4(VertexPosition,1.0);
}