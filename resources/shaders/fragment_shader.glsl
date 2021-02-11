#version 330 core
in vec2 TexCoord;
in vec3 diffuse;
in float distance;

out vec4 color;

uniform sampler2D Texture;
uniform vec2 resolution;

void main()
{
	vec4 objectColor = texture(Texture, TexCoord);

	vec4 color_2 = vec4(objectColor.rgb * (diffuse + vec3(0.7)), objectColor.a);

	color = color_2;
	
	//vec2 uv = vec2(gl_FragCoord.x / resolution.x - 0.5, gl_FragCoord.y / resolution.y - 0.5);
	//float len = max(min(0.4 / length(uv), 1.0), 0.0);
	//len *= len * len;
	
	//color.xyz *= len;
}