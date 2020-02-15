

#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
	vec3 gammaResult = pow(texture(skybox, TexCoords).rgb, vec3(1.0f/2.2f));
    FragColor = vec4(gammaResult, 1.0f);
}

