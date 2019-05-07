#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
in vec3 spriteC;

in vec4 pos;
uniform vec2 light_pos;

void main()
{    
    float intensity = 1.0 / length(pos.xy - light_pos);
    color = vec4(spriteC, 1.0) * texture(image, TexCoords);
    color = color * intensity;
} 