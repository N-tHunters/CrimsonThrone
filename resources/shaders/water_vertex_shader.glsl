#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out float shading;
out float specular;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 cameraRot;
uniform float time;
uniform vec3 lightPos;
uniform vec3 objectPos;
uniform vec3 cameraPos;

vec3 normalize(vec3 input_vector) {
	float length = sqrt(input_vector.x * input_vector.x + input_vector.y * input_vector.y + input_vector.z * input_vector.z);
	vec3 output_vector = input_vector / length;
	return output_vector;
}

float dist(vec3 input_vector) {
	float length = sqrt(input_vector.x * input_vector.x + input_vector.y * input_vector.y + input_vector.z * input_vector.z);
	return length;
}

void main()
{
	vec3 lightVec = lightPos - position - objectPos;
    lightVec *= -1.0;
	lightVec = normalize(lightVec);
	float lightVecL = dist(lightVec);

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - position - objectPos);
	vec3 viewDir = normalize(cameraPos - position - objectPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	//float specular = 1024 * spec * 100.0;
	float specular = 10;

    gl_Position = projection * cameraRot * view * model * vec4(position.x, position.y - abs(sin((position.x + objectPos.x - position.z - objectPos.z) * 10.0 - time) / 2.0), position.z, 1.0f);

    shading = (lightVec.x * normal.x + lightVec.y * normal.y + lightVec.z * lightVec.z);
    shading = 1.0 + (shading) / 3.0;
    shading -= lightVecL / 100.0;

    print(shading);

    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}