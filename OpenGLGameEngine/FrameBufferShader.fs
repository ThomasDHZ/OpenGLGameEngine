#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D Layer[30];

void main()
{
    vec3 col = texture(Layer[0], TexCoords).rgb;

	for(int x = 1; x <= 30; x++)
	{
		if(texture(Layer[x], TexCoords).r > 0.0f &&
		   texture(Layer[x], TexCoords).g > 0.0f &&
		   texture(Layer[x], TexCoords).b > 0.0f)
		{
			if(texture(Layer[x], TexCoords).a == 0.0f)
			{
				col = texture(Layer[x-1], TexCoords).rgb;
			}
			else
			{
				if(texture(Layer[x], TexCoords).a == 1.0f)
				{
					col = texture(Layer[x], TexCoords).rgb;
				}
				else
				{
					col *= texture(Layer[x], TexCoords).rgb;
				}
			}
		}
	}

    FragColor = vec4(col, 1.0);
} 

