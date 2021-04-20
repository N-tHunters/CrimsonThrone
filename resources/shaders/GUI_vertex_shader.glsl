#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 2) in vec2 texCoord;

uniform vec2 resolution;
uniform vec2 objectpos;

out vec2 TexCoord;
void main()
{
	vec3 normalized_position = vec3((pos.x + objectpos.x) / resolution.x * 2.0f - 1.0f, (pos.y + objectpos.y) / resolution.y * 2.0f - 1.0f, pos.z);
    
    gl_Position = vec4(normalized_position, 1.0f);

    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}