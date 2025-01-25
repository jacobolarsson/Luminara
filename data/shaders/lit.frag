#version 460 core

in vec3 fragPos_view;
in vec2 UV;
in vec3 normal_view;

uniform sampler2D myTexture;
uniform vec3 lightPos_view;
uniform vec3 lightColor;
uniform float constAtt;
uniform float linAtt;
uniform float quadAtt;

out vec4 FragColor;

void main()
{
    vec3 lightVec_view = normalize(lightPos_view - fragPos_view);

    vec3 ambient = 0.4 * lightColor;
    vec3 diffuse = lightColor * max(dot(normal_view, lightVec_view), 0.0);

    vec3 reflectDir = reflect(-lightVec_view, normal_view);
    float spec = pow(max(dot(normalize(-fragPos_view), reflectDir), 0.0), 64);
    vec3 specular = 0.5 * spec * lightColor;

    float dist = length(lightPos_view - fragPos_view);
    float att = 1.0 / (constAtt + linAtt * dist + quadAtt * (dist * dist));    

    ambient *= att;  
    diffuse *= att;
    specular *= att;   

    vec3 result = (ambient + diffuse + specular) * vec3(0.2, 0.1, 0.7);

    FragColor = vec4(result, 1.0);
} 