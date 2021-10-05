#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture;

void main()
{
	vec4 objectColor1 = texture(Texture1, TexCoord);
	vec4 objectColor2 = texture(Texture2, TexCoord);

	color = texture(Texture, TexCoord);
}