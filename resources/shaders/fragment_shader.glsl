#version 330 core
in vec2 TexCoord;
in float visibility;

out vec4 color;

uniform sampler2D Texture;
uniform vec3 skyColor;

void main()
{
    color = texture(Texture, TexCoord);
    //color = mix(vec4(skyColor, 1.0), color, visibility);
}