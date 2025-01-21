#version 460 core

in vec2 UV;
in vec3 normal;

uniform sampler2D myTexture;
uniform vec3 lightVector;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
    vec3 ambient = 0.1 * lightColor;
    vec3 diffuse = lightColor * max(dot(normal, lightVector), 0.0);
    vec3 result = (ambient + diffuse) * vec3(0.6, 0.6, 0.6);

    FragColor = vec4(result, 1.0);


//    FragColor =  texture(myTexture, UV);
} 