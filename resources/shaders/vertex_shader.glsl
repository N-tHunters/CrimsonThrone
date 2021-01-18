#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out float shading;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 cameraRot;
uniform vec3 lightPos;
uniform vec3 objectPos;

void main()
{
	vec3 lightVec = lightPos - position - objectPos;
    lightVec *= -1.0;
	float lightVecL = sqrt(lightVec.x * lightVec.x + lightVec.y * lightVec.y + lightVec.z * lightVec.z);
	lightVec /= lightVecL;

    gl_Position = projection * cameraRot * view * model * vec4(position, 1.0f);

    shading = (lightVec.x * normal.x + lightVec.y * normal.y + lightVec.z * lightVec.z) + 3.0;
    shading = (6.0 - shading) / 3.0;
    shading -= lightVecL / 100.0;

    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}