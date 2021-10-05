#version 330 core
layout (location = 0) in vec3 position; // <vec3 position, vec2 texCoords>
layout (location = 1) in vec2 texCords; // <vec3 position, vec2 texCoords>

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 cameraRot;
uniform vec3 offset;
uniform vec4 color;
uniform float scale;

void main()
{
    ParticleColor = color;
    TexCoords = texCords;
    gl_Position = projection * cameraRot * view * vec4((position * scale) + offset, 1.0);
}
