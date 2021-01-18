#version 330 core
in vec2 TexCoord;
in float shading;
//in float visibility;

out vec4 color;

uniform sampler2D Texture;
uniform vec3 skyColor;

void main()
{
    color = mix(vec4(vec3(0.0), 1.0), texture(Texture, TexCoord), shading);
}