#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
in vec3 spriteC;

void main()
{    
    color = vec4(spriteC, 1.0) * texture(image, TexCoords);
} 