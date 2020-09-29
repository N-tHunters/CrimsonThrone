#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 cameraRot;

const float density = 0.007;
const float gradient = 1.5;

void main()
{
    gl_Position = projection * cameraRot * view * model * vec4(position, 1.0f);
    //gl_Position = projection * vec4(position, 1.0f);
    float distance = length(gl_Position.xyz);
    float visibility = exp(-pow(distance * density, gradient));
    visibility = clamp(visibility, 0.0, 1.0);

    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}