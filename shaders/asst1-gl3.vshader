#version 130

uniform float uVertexScale;

in vec2 aVertex;
in vec3 aColor;
in vec2 aTexCoord;

out vec3 vColor;
out vec2 vTexCoord;

void main() {
  gl_Position = vec4(aVertex.x * uVertexScale, aVertex.y, 0,1);
  vColor = aColor;
  vTexCoord = aTexCoord;
}
