#version 330 core
layout (location = 0) in vec3 position;
// layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 diffuse;
out vec3 specular;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 cameraRot;
uniform float time;
uniform vec3 lightPos;
uniform vec3 objectPos;
uniform vec3 cameraPos;

void main()
{
	vec3 Position = vec3(position.x, position.y - abs(sin((position.x + objectPos.x - position.z - objectPos.z) * 10.0 - time) / 2.0), position.z);
	vec3 Position2 = vec3(position.x - 1.0, position.y - abs(sin((position.x - 1.0 + objectPos.x - position.z - objectPos.z) * 10.0 - time) / 2.0), position.z);
	vec3 Position3 = vec3(position.x, position.y - abs(sin((position.x + objectPos.x - position.z + 1.0 - objectPos.z) * 10.0 - time) / 2.0), position.z - 1.0);
	
	vec3 Vec1 = Position3 - Position;
	vec3 Vec2 = Position2 - Position;

	vec3 normal = vec3(Vec1.y * Vec2.z - Vec1.z * Vec2.y,
				  Vec1.z * Vec2.x - Vec1.x * Vec2.z,
				  Vec1.x * Vec2.y - Vec1.y * Vec2.x);
	
	vec3 norm = normalize(normal);
	
	vec3 lightDir = lightPos - objectPos - position;
	
	float lightVecL = length(lightDir);
	lightVecL = max(lightVecL, 1.0f);
	lightDir = normalize(lightDir);

    float diff = max(dot(norm, lightDir), 0.0);
   	diffuse = vec3(min(diff * 1.0 / lightVecL * 10.0, 1.0));

   	vec3 viewDir = normalize(cameraPos - position - objectPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	specular = vec3(min(10.0 * spec * 1.0 / lightVecL, 1.0));

    gl_Position = projection * cameraRot * view * model * vec4(Position, 1.0f);

    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
