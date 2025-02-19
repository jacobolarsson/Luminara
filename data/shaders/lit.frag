#version 460 core

struct Material 
{
    sampler2D ambientTex;
    sampler2D diffuseTex;
    sampler2D specularTex;    
    sampler2D normalMap;    
}; 

uniform Material material;

in VsOut 
{
    vec3 fragPos_tan;
    vec3 lightPos_tan;
    vec3 viewPos_tan;
    vec2 UV; 
} fsIn;

uniform vec3 lightColor;
uniform float constAtt;
uniform float linAtt;
uniform float quadAtt;

out vec4 FragColor;

void main()
{
    vec3 lightVec_tan = normalize(fsIn.lightPos_tan - fsIn.fragPos_tan);
    vec3 viewVec_tan = normalize(fsIn.viewPos_tan - fsIn.fragPos_tan);

    vec3 normal_tan = texture(material.normalMap, fsIn.UV).rgb;
    // Change from the [0, 1] component range to [-1, 1]
    normal_tan = normalize(normal_tan * 2.0 - 1.0); 

    vec3 ambient = 0.4 * lightColor;
    vec3 diffuse = lightColor * max(dot(normal_tan, lightVec_tan), 0.0);

    vec3 halfwayVec = normalize(lightVec_tan + viewVec_tan);
    float spec = pow(max(dot(normal_tan, halfwayVec), 0.0), 128);
    vec3 specular = 0.5 * spec * lightColor;

    float dist = length(fsIn.lightPos_tan - fsIn.fragPos_tan);
    float att = 1.0 / (constAtt + linAtt * dist + quadAtt * (dist * dist));    

    ambient *= att;  
    diffuse *= att;
    specular *= att;   

    vec4 diffColor = texture(material.diffuseTex, fsIn.UV);
    if (diffColor.a < 0.5) {
        discard;
    }

    vec3 result = diffuse * vec3(diffColor);
    result += ambient * texture(material.ambientTex, fsIn.UV).rgb;
    result += specular * texture(material.specularTex, fsIn.UV).rgb;

    FragColor = vec4(result, 1.0);
} 
