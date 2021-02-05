#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 900.0;  

void main()
{
    // vec2 offsets[9] = vec2[](
    //     vec2(-offset,  offset), // top-left
    //     vec2( 0.0f,    offset), // top-center
    //     vec2( offset,  offset), // top-right
    //     vec2(-offset,  0.0f),   // center-left
    //     vec2( 0.0f,    0.0f),   // center-center
    //     vec2( offset,  0.0f),   // center-right
    //     vec2(-offset, -offset), // bottom-left
    //     vec2( 0.0f,   -offset), // bottom-center
    //     vec2( offset, -offset)  // bottom-right    
    // );

    // float kernel[9] = float[](
    //     -1,  2, -1,
    //      2, -3,  2,
    //     -1,  2, -1
    // );
    
    // vec3 sampleTex[9];
    // for(int i = 0; i < 9; i++)
    // {
    //    sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    // }

    // vec3 col = vec3(0.0);
    // for(int i = 0; i < 9; i++)
    //     col += sampleTex[i] * kernel[i];

    vec3 col = texture(screenTexture, TexCoords).xyz;

    // float l = length((TexCoords - vec2(0.5)) * 2.0);
    // float sqrt_2 = sqrt(2);

    // col *= 1.0 - l / sqrt_2 / 2.0;

    FragColor = vec4(col, 1.0);
}