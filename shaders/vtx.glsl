#version 120
attribute vec2 pos;
attribute vec2 in_tex_coord;
varying vec2 TexCoord;
void main()
{
    gl_Position = vec4(pos, 0.0, 1.0);
    TexCoord = in_tex_coord;
}
