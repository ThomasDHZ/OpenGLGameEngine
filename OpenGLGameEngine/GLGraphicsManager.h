#pragma once
#include "ShaderCompiler.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "MainShader.h"
#include <vector>

class GLGraphicsManager
{
private:
	 unsigned int BoundVertexArrayObjectID;
	// unsigned int BoundShaderProgramID;

	 unsigned int BoundVertexShader;
	 unsigned int BoundFragmentShader;

	 ShaderCompiler compiler;
	 std::vector<Shader> ShaderList;

public:
	GLGraphicsManager();

	void BindVAO(unsigned int VAO);
	void BindShaderProgram(unsigned int VertexShader, unsigned int FragmentShader);
	void CompileVertexShader(const char* FileName);
	void CompileFragmentShader(const char* FileName);
	void UseShaderProgram(unsigned int ShaderProgram);

	unsigned int GetVAOID() { return BoundVertexArrayObjectID; }
	unsigned int GetVertexShader() { return BoundVertexShader; }
	unsigned int GetFragmentShader() { return BoundFragmentShader; };
	//unsigned int GetShaderProgram() { return BoundShaderProgramID; };

	MainShader* GetMainShader()
	{
		return static_cast<MainShader*>(&ShaderList[0]);
	}
};
