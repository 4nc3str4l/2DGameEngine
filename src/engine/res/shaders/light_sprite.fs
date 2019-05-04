#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec2 light_pos; 

in vec3 spriteC;
in vec4 pos;

void main()
{    
    float intensity = 0.25 / length(pos.xy - light_pos);
    color = vec4(spriteC, 1.0) * texture(image, TexCoords);
    color *= intensity;
} 