#version 130

uniform float uVertexScale;
uniform sampler2D uTexUnit0;

in vec2 vTexCoord;
in vec3 vColor;

out vec4 fragColor;

void main(void) {
  vec4 texColor0 = vec4(vColor.x, vColor.y, vColor.z, 1);
  vec4 texColor1 = texture(uTexUnit0, vTexCoord);

  float lerper = clamp(.3 *uVertexScale,0.,1.);

  fragColor = (lerper)*texColor1 + (1.-lerper)*texColor0;
}
