#include "MainShader.h"

MainShader::MainShader() : Shader()
{
}

MainShader::MainShader(unsigned int ShaderID, ShaderType shaderType) : Shader(ShaderID, shaderType)
{
}

MainShader::~MainShader()
{
}

void MainShader::SetShaderModelValue(glm::mat4& Matrix) const
{
	SetShaderMat4Value("model", Matrix);
}

void MainShader::SetShaderProjectionValue(glm::mat4& projection) const
{
	SetShaderMat4Value("projection", projection);
}

void MainShader::SetShaderViewnValue(glm::mat4& view) const
{
	SetShaderMat4Value("view", view);
}
