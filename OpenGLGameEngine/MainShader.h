#pragma once
#include "Shader.h"

class MainShader : public Shader
{
private:
public:
	MainShader();
	MainShader(unsigned int ShaderID, ShaderType shaderType);
	~MainShader();

	void SetShaderModelValue(glm::mat4& Matrix) const;
	void SetShaderProjectionValue(glm::mat4& projection) const;
	void SetShaderViewnValue(glm::mat4& view) const;
};

