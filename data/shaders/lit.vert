#version 460 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec3 inTangent;
layout (location = 3) in vec3 inBitangent;
layout (location = 4) in vec2 inUV;

out VsOut
{
    vec3 fragPos_tan;
    vec3 lightPos_tan;
    vec3 viewPos_tan;
    vec2 UV;    
} vsOut;

uniform mat4 modelMtx;
uniform mat4 normalMtx;
uniform mat4 viewMtx;
uniform mat4 projectionMtx;

uniform vec3 lightPos_world;
uniform vec3 viewPos_world;

void main()
{
    vec3 norm_world = normalize(mat3(normalMtx) * inNormal);
    vec3 tang_world = normalize(mat3(normalMtx) * inTangent);
    vec3 bitan_world = normalize(mat3(normalMtx) * inBitangent);

    // Re-orthogonalize the tangent vector due to possible averaging while loading the model
    tang_world = normalize(tang_world - dot(tang_world, norm_world) * norm_world);
//    vec3 bitan_world = normalize(cross(norm_world, tang_world));

    mat3 tangentMtx = transpose(mat3(tang_world, bitan_world, norm_world));

    vsOut.fragPos_tan = tangentMtx * vec3(modelMtx * vec4(inPos, 1.0));
    vsOut.lightPos_tan = tangentMtx * lightPos_world;
    vsOut.viewPos_tan = tangentMtx * viewPos_world;
    vsOut.UV = inUV;

    gl_Position = projectionMtx * viewMtx * modelMtx * vec4(inPos, 1.0);
}