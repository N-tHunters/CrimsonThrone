#version 330 core
in vec2 TexCoord;
in float shading;
//in float visibility;

out vec4 color;

uniform sampler2D Texture;
uniform vec3 skyColor;

void main()
{
    //color = texture(Texture, TexCoord);
    color = mix(vec4(vec3(0.0), 1.0), texture(Texture, TexCoord), shading);
    color.a = 0.6;
    //color = mix(vec4(skyColor, 1.0), color, visibility);
}