#include "PointLight.h"

PointLight::PointLight()
{
	PointLightID = 0;
}

PointLight::PointLight(glm::vec3 Position, unsigned int pointLightID)
{
	PointLightID = pointLightID;
	PointerLight = PointLightStruct{ Position };
}

PointLight::PointLight(PointLightStruct light, unsigned int pointLightID)
{
	PointLightID = pointLightID;
	PointerLight = light;
}

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, unsigned int pointLightID)
{
	PointLightID = pointLightID;
	PointerLight = PointLightStruct{ position, ambient, diffuse, specular, constant, linear, quadratic };
}

PointLight::~PointLight()
{
}

void PointLight::Update(Shader2& shader)
{
	auto a = std::to_string(PointLightID);
	shader.setVec3("pointLights[" + std::to_string(PointLightID) + "].position", PointerLight.Position);
	shader.setVec3("pointLights[" + std::to_string(PointLightID) + "].ambient", PointerLight.Ambient);
	shader.setVec3("pointLights[" + std::to_string(PointLightID) + "].diffuse", PointerLight.Diffuse);
	shader.setVec3("pointLights[" + std::to_string(PointLightID) + "].specular", PointerLight.Specular);
	shader.setFloat("pointLights[" + std::to_string(PointLightID) + "].constant", PointerLight.Constant);
	shader.setFloat("pointLights[" + std::to_string(PointLightID) + "].linear", PointerLight.Linear);
	shader.setFloat("pointLights[" + std::to_string(PointLightID) + "].quadratic", PointerLight.Quadratic);
}

PointLight& PointLight::operator=(const PointLight& rhs)
{
	PointLightID = rhs.PointLightID;
	PointerLight = rhs.PointerLight;
	return *this;
}

