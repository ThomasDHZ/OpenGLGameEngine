
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
	col = pow(col, vec3(1.0f/2.2f));
    FragColor = vec4(col, 1.0);
} 


