#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D screenTexture2;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;

	if(texture(screenTexture2, TexCoords).a == 0.0f)
	{
		col = texture(screenTexture, TexCoords).rgb;
	}
	else
	{
		if(texture(screenTexture2, TexCoords).a == 1.0f)
		{
			col = texture(screenTexture2, TexCoords).rgb;
		}
		else
		{
			col *= texture(screenTexture2, TexCoords).rgb;
		}
	}

    FragColor = vec4(col, 1.0);
} 

