#version 120
uniform vec4 color;
varying vec2 TexCoord;
uniform sampler2D sampler;
void main()
{
    gl_FragColor = texture2D(sampler, TexCoord);
}
