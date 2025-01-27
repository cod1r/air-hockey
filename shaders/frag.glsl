#version 120
uniform bool no_texture;
uniform vec4 color;
varying vec2 TexCoord;
uniform sampler2D sampler;
void main()
{
  if (no_texture) {
    gl_FragColor = color;
  } else {
    gl_FragColor = texture2D(sampler, TexCoord);
  }
}
