#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "ShaderTypeEnum.h"

class Shader
{
private:
	unsigned int ShaderID;
	ShaderType Type;

protected:
	void InitializeTextureSampler(const std::string TextureValueName, unsigned int TextureSamplerLocation) const;

	void SetShaderBoolValue(const std::string& name, bool value) const;
	void SetShaderIntValue(const std::string& name, int value) const;
	void SetShaderFloatValue(const std::string& name, float value) const;
	void SetShaderVec2Value(const std::string& name, float x, float y) const;
	void SetShaderVec3Value(const std::string& name, float x, float y, float z) const;
	void SetShaderVec4Value(const std::string& name, float x, float y, float z, float w) const;
	void SetShaderMat2Value(const std::string& name, const glm::mat2& mat) const;
	void SetShaderMat3Value(const std::string& name, const glm::mat3& mat) const;
	void SetShaderMat4Value(const std::string& name, const glm::mat4& mat) const;

public:
	Shader();
	Shader(unsigned int shaderID, ShaderType type);
	virtual ~Shader();
	virtual Shader& operator=(Shader& rhs);
	unsigned int GetShaderID();
	ShaderType GetShaderType();
	void DeleteShader();
};

