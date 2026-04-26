#version 330 core

layout (location = 0) in vec2 pos;

out vec2 uv;

void main()
{
    uv = pos * .5f + .5f;
    gl_Position = vec4(pos, .0f, 1.f);
}
