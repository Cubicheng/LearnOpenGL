#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform float shininess;

uniform vec3 viewPos;

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4

uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcPointLight(PointLight light){
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 lightDir = normalize(FragPos - light.position);

    float diff = max(dot(Normal,-lightDir),0.0);

    vec3 reflectDir = reflect(lightDir,Normal);
    float spec = pow( max(dot(viewDir,reflectDir),0.0) , shininess);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic*distance*distance);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1,TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1,TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1,TexCoords));

    return attenuation*(ambient + diffuse + specular);
}


struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform SpotLight spotlight;

vec3 CalcSpotLight(SpotLight light){

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 lightDir = normalize(FragPos - light.position);

    float diff = max(dot(Normal,-lightDir),0.0);

    vec3 reflectDir = reflect(lightDir,Normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic*distance*distance);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1,TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1,TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1,TexCoords));

    float theta = dot(lightDir,normalize(light.direction));
    float epsilon = light.cutOff - light.outCutOff;
    float intensity = clamp( (theta-light.outCutOff)/epsilon, 0.0 , 1.0);

    diffuse *= intensity;
    spec *= intensity;

    return attenuation*(ambient + diffuse + specular);
}

void main(){

    vec3 result = vec3(0.0);

    for(int i=0; i<NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i]);
    
    //result += CalcSpotLight(spotlight);
     
    FragColor = vec4( result, 1.0 );
}