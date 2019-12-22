#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(glm::vec3 Direction)
{
	DirectLight = DirectionalLightStruct{ Direction };
}

DirectionalLight::DirectionalLight(DirectionalLightStruct light)
{
	DirectLight = light;
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	DirectLight = DirectionalLightStruct{ direction, ambient, diffuse, specular };
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::Update(Shader2& shader)
{
	shader.setVec3("dirLight.direction", DirectLight.Direction);
	shader.setVec3("dirLight.ambient", DirectLight.Ambient);
	shader.setVec3("dirLight.diffuse", DirectLight.Diffuse);
	shader.setVec3("dirLight.specular", DirectLight.Specular);
}

DirectionalLight& DirectionalLight::operator=(const DirectionalLight& rhs)
{
	DirectLight = rhs.DirectLight;
	return *this;
}
