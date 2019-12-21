#pragma once
#include <glm\ext\vector_float3.hpp>
#include "Shader.h"
#include "shader_m.h"

struct DirectionalLightStruct
{
	glm::vec3 Direction = glm::vec3(0.0f);
	glm::vec3 Ambient = glm::vec3(0.00005f, 0.00005f, 0.00005f);
	glm::vec3 Diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	glm::vec3 Specular = glm::vec3(0.5f, 0.5f, 0.5f);

	DirectionalLightStruct()
	{
	}
	DirectionalLightStruct(glm::vec3 direction)
	{
		Direction = direction;
	}
	DirectionalLightStruct(float x, float y, float z)
	{
		Direction = glm::vec3(x,y,z);
	}
	DirectionalLightStruct(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	{
		Direction = direction;
		Ambient = ambient;
		Diffuse = diffuse;
		Specular = specular;
	}
};

class DirectionalLight
{
private:
	DirectionalLightStruct DirectLight;
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 Direction);
	DirectionalLight(DirectionalLightStruct light);
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~DirectionalLight();

	void Update(Shader2& shader);

	void SetDirection(glm::vec3 Direction) { DirectLight.Direction = Direction; }
	void SetAmbient(glm::vec3 Ambient) { DirectLight.Ambient = Ambient; }
	void SetDiffuse(glm::vec3 Diffuse) { DirectLight.Diffuse = Diffuse; }
	void SetSpecular(glm::vec3 Specular) { DirectLight.Specular = Specular; }
	void SetDirectLight(DirectionalLightStruct light) { DirectLight = light; }

	glm::vec3 GetDirection() { return DirectLight.Direction; }
	glm::vec3 GetAmbient() { return DirectLight.Ambient; }
	glm::vec3 GetDiffuse() { return DirectLight.Diffuse; }
	glm::vec3 GetSpecular() { return DirectLight.Specular; }
	DirectionalLightStruct GetDirectLight() { return DirectLight; }

	DirectionalLight& operator=(const DirectionalLight& rhs);
};

