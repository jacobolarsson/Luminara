#version 460 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;

out vec3 fragPos_view;
out vec2 UV;
out vec3 normal_view;

uniform mat4 modelMtx;
uniform mat4 normalMtx;
uniform mat4 viewMtx;
uniform mat4 projectionMtx;

void main()
{
    fragPos_view = vec3(viewMtx * modelMtx * vec4(inPos, 1.0));
    normal_view = vec3(normalMtx * vec4(inNormal, 0.0));
    UV = inUV;

    gl_Position = projectionMtx * vec4(fragPos_view, 1.0f);
}