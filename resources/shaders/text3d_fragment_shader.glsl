#version 330 core
in vec2 TexCoord;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 t = texture(text, TexCoord);
    color = vec4(textColor.r, textColor.g, textColor.b, t.r);
}