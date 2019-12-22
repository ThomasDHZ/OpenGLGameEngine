#pragma once
#include <glm\ext\vector_float3.hpp>
#include "../OpenGL.Graphics3D/shader_m.h"

struct PointLightStruct
{
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 Diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 Specular = glm::vec3(1.0f, 1.0f, 1.0f);
	float Constant = 1.0f;
	float Linear = .32f;
	float Quadratic = .032;

	PointLightStruct()
	{
	}
	PointLightStruct(glm::vec3 position)
	{
		Position = position;
	}
	PointLightStruct(float x, float y, float z)
	{
		Position = glm::vec3(x, y, z);
	}
	PointLightStruct(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
	{
		Position = position;
		Ambient = ambient;
		Diffuse = diffuse;
		Specular = specular;
		Constant = constant;
		Linear = linear;
		Quadratic = quadratic;
	}
};

class PointLight
{
private:
	unsigned int PointLightID;
	PointLightStruct PointerLight;
public:
	PointLight();
	PointLight(glm::vec3 Position, unsigned int pointLightID);
	PointLight(PointLightStruct light, unsigned int pointLightID);
	PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, unsigned int pointLightID);
	~PointLight();

	void Update(Shader2& shader);

	void SetPosition(glm::vec3 Position) { PointerLight.Position = Position; }
	void SetAmbient(glm::vec3 Ambient) { PointerLight.Ambient = Ambient; }
	void SetDiffuse(glm::vec3 Diffuse) { PointerLight.Diffuse = Diffuse; }
	void SetSpecular(glm::vec3 Specular) { PointerLight.Specular = Specular; }
	void SetConstant(float Constant) { PointerLight.Constant = Constant; }
	void SetLinear(float Linear) { PointerLight.Linear = Linear; }
	void SetQuadratic(float Quadratic) { PointerLight.Quadratic = Quadratic; }
	void SetPointLight(PointLightStruct light) { PointerLight = light; }

	glm::vec3 GetPosition() { return PointerLight.Position; }
	glm::vec3 GetAmbient() { return PointerLight.Ambient; }
	glm::vec3 GetDiffuse() { return PointerLight.Diffuse; }
	glm::vec3 GetSpecular() { return PointerLight.Specular; }
	float GetConstant() { return PointerLight.Constant; }
	float GetLinear() { return PointerLight.Linear; }
	float GetQuadratic() { return PointerLight.Quadratic; }
	PointLightStruct GetPointLight() { return PointerLight; }

	PointLight& operator=(const PointLight& rhs);
};

