#version 330 core
in vec2 TexCoord;
in vec3 diffuse;
in float underWater2;
//in float visibility;

out vec4 color;

uniform sampler2D Texture;
uniform vec3 skyColor;

void main()
{
    // color = mix(vec4(vec3(0.0), 1.0), texture(Texture, TexCoord), shading);
    vec4 objectColor = texture(Texture, TexCoord);
    // vec3 objectColor = vec3(1.0);
    // color = vec4(pcolor.r * diffuse.x, pcolor.g * diffuse.y, pcolor.b * diffuse.z, pcolor.a);
    color = vec4(objectColor.rgb * (diffuse + vec3(0.7)), objectColor.a);
}