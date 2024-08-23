#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emmision;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main(){

    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords)) * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(FragPos - light.position);
    float diff = max( dot(norm, -lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * lightColor * vec3(texture(material.diffuse,TexCoords));

    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect( lightDirection, norm );
    float spec = pow( max( dot( viewDirection, reflectDirection ), 0.0 ), material.shininess );
    vec3 specular = light.specular * vec3(texture(material.specular,TexCoords)) * spec * lightColor;

    vec3 emmision = vec3(texture(material.emmision,TexCoords));

    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);



    float theta = dot( lightDirection, normalize(light.direction) );
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp( (theta - light.outerCutOff)/epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4( attenuation*result, 1.0 );
}