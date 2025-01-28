#version 460 core

in vec3 fragPos_view;
in vec2 UV;
in vec3 normal_view;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;    
}; 

uniform Material material;

uniform vec3 lightPos_view;
uniform vec3 lightColor;
uniform float constAtt;
uniform float linAtt;
uniform float quadAtt;

out vec4 FragColor;

void main()
{
    vec3 lightVec_view = normalize(lightPos_view - fragPos_view);
    vec3 viewVec = normalize(-fragPos_view);

    vec3 ambient = 0.3 * lightColor;
    vec3 diffuse = lightColor * max(dot(normal_view, lightVec_view), 0.0);

    vec3 halfwayVec = normalize(lightVec_view + viewVec);
    float spec = pow(max(dot(normal_view, halfwayVec), 0.0), 128);
    vec3 specular = 0.5 * spec * lightColor;

    float dist = length(lightPos_view - fragPos_view);
    float att = 1.0 / (constAtt + linAtt * dist + quadAtt * (dist * dist));    

    ambient *= att;  
    diffuse *= att;
    specular *= att;   

    vec3 result = (ambient + diffuse) * texture(material.diffuse, UV).rgb;
    result += specular * texture(material.specular, UV).rgb;

    FragColor = vec4(result, 1.0);
} 
