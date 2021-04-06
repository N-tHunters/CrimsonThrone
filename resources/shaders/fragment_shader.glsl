#version 330 core
in vec2 TexCoord;
in vec3 diffuse;
in float distance;
in float texBlendOut;

out vec4 color;

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform vec2 resolution;

void main()
{
	vec4 objectColor1 = texture(Texture1, TexCoord);
	vec4 objectColor2 = texture(Texture2, TexCoord);

	vec4 color_1 = vec4(objectColor1.rgb * (diffuse + vec3(0.7)), objectColor1.a);
	vec4 color_2 = vec4(objectColor2.rgb * (diffuse + vec3(0.7)), objectColor2.a);

	// color_2 = mix(color_2, vec4(0.5f, 0.7f, 0.7f, 1.0f), min(distance / 100.0, 1.0));

	color = mix(color_1, color_2, texBlendOut);
	
	//vec2 uv = vec2(gl_FragCoord.x / resolution.x - 0.5, gl_FragCoord.y / resolution.y - 0.5);
	//float len = max(min(0.4 / length(uv), 1.0), 0.0);
	//len *= len * len;
	
	//color.xyz *= len;
}