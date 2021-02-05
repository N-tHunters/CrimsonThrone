#version 330 core
in vec2 TexCoord;
in vec3 diffuse;
in vec3 specular;
in vec2 resolution;
//in float visibility;

out vec4 color;

uniform sampler2D Texture;
uniform vec3 skyColor;

void main()
{
    // color = mix(vec4(vec3(0.0), 1.0), texture(Texture, TexCoord), specular + shading);
    vec4 objectColor = texture(Texture, TexCoord);
    color = vec4(objectColor.rgb * (diffuse + vec3(0.5) + specular), 0.6);
    //vec3 col = vec3(gl_FragCoord.w);
    //color = vec4(col, 0.5);
}