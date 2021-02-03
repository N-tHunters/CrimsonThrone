#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 diffuse;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 cameraRot;
uniform vec3 lightPos;
uniform vec3 objectPos;
uniform vec3 cameraPos;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDir = lightPos - position - objectPos;
	float lightVecL = length(lightDir);
	lightDir = normalize(lightDir);

	float diff = max(dot(norm, lightDir), 0.0);
	diffuse = vec3(min(diff / lightVecL * 100.0, 1.0));

	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
	gl_Position = projection * cameraRot * view * model * vec4(position, 1.0f);
}