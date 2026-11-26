#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

in vec3 normal;
in vec3 crntPos;

uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main(){
    float ambient = 0.20f;

    vec3 normal = normalize(normal);
    vec3 lightDirection = normalize(lightPos - crntPos);

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient);
}