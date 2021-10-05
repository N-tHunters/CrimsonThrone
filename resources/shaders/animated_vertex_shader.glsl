#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 jointIndices;
layout (location = 4) in vec3 weights;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 cameraRot;

uniform mat4 jointTransforms[50];

void main()
{
	vec4 total_local_pos = vec4(0);

	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);

	for (int i = 0; i < 50; i ++) {
		vec4 local_pos = jointTransforms[jointIndices[i]] * vec4(position, 1.0f);
		total_local_pos += local_pos * weights[i];
	}

	gl_Position = projection * cameraRot * view * model * total_local_pos;
}