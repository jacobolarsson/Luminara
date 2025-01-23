#version 460 core
layout (location = 0) in vec3 inPos;

uniform mat4 modelMtx;
uniform mat4 viewMtx;
uniform mat4 projectionMtx;

void main()
{
    gl_Position = projectionMtx * viewMtx * modelMtx * vec4(inPos, 1.0);
}