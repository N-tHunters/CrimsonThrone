#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

uniform vec2 resolution;

out vec2 TexCoord;
void main()
{
	vec3 pos = vec3(position.x / resolution.x * 2.0f - 1.0f, position.y / resolution.y * 2.0f - 1.0f, position.z);
    gl_Position = vec4(pos, 1.0f);
    //float distance = length(gl_Position.xyz);
    //float visibility = exp(-pow(distance * density, gradient));
    //visibility = clamp(visibility, 0.0, 1.0);

    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}