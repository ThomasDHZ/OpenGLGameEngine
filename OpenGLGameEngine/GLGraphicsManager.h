#pragma once
#include "ShaderCompiler.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class GLGraphicsManager
{
private:
	 unsigned int BoundVertexArrayObjectID;
	 unsigned int BoundShaderProgramID;

	 unsigned int BoundVertexShader;
	 unsigned int BoundFragmentShader;

	 ShaderCompiler compiler;

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
	GLGraphicsManager();

	void BindVAO(unsigned int VAO);
	void BindShaderProgram(unsigned int VertexShader, unsigned int FragmentShader);
	void CompileVertexShader(const char* FileName);
	void CompileFragmentShader(const char* FileName);
	void UseShaderProgram(unsigned int ShaderProgram);

	void SetShaderModelValue(glm::mat4& Matrix) const
	{
		SetShaderMat4Value("model", Matrix);
	}

	void SetShaderProjectionValue(glm::mat4& projection) const
	{
		SetShaderMat4Value("projection", projection);
	}

	void SetShaderViewnValue(glm::mat4& view) const
	{
		SetShaderMat4Value("view", view);
	}

	unsigned int GetVAOID() { return BoundVertexArrayObjectID; }
	unsigned int GetVertexShader() { return BoundVertexShader; }
	unsigned int GetFragmentShader() { return BoundFragmentShader; };
	unsigned int GetShaderProgram() { return BoundShaderProgramID; };
};
