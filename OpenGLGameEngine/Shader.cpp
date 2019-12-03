#include "Shader.h"

Shader::Shader()
{
	ShaderID = 0;
	Type = ShaderType::Undefined;
}

Shader::Shader(unsigned int shaderID, ShaderType type)
{
	ShaderID = shaderID;
	Type = type;
}

Shader::~Shader()
{
}

Shader& Shader::operator=(Shader& rhs)
{
	ShaderID = rhs.ShaderID;
	Type = rhs.Type;

	return* this;
}

unsigned int Shader::GetShaderID()
{
	return ShaderID;
}

ShaderType Shader::GetShaderType()
{
	return Type;
}

void Shader::InitializeTextureSampler(const std::string TextureValueName, unsigned int TextureSamplerLocation) const
{
	SetShaderIntValue(TextureValueName, TextureSamplerLocation);
}

void Shader::SetShaderBoolValue(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ShaderID, name.c_str()), (int)value);
}

void Shader::SetShaderIntValue(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ShaderID, name.c_str()), value);
}

void Shader::SetShaderFloatValue(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ShaderID, name.c_str()), value);
}

void Shader::SetShaderVec2Value(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ShaderID, name.c_str()), x, y);
}

void Shader::SetShaderVec3Value(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ShaderID, name.c_str()), x, y, z);
}

void Shader::SetShaderVec4Value(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ShaderID, name.c_str()), x, y, z, w);
}

void Shader::SetShaderMat2Value(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetShaderMat3Value(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetShaderMat4Value(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::DeleteShader()
{
	glDeleteShader(ShaderID);
}