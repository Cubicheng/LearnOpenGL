#version 330 core

in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;

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

    vec3 ambient = light.ambient * material.ambient * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);
    float diff = max( dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * lightColor * material.diffuse;

    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect( -lightDirection, norm );
    float spec = pow( max( dot( viewDirection, reflectDirection ), 0.0 ), material.shininess );
    vec3 specular = light.specular * material.specular * spec * lightColor;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4( result, 1.0 );
}