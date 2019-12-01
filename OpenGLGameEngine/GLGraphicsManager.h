#pragma once
#include "ShaderCompiler.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "MainShader.h"
#include "ScreenBufferShader.h"

class GLGraphicsManager
{
private:
	 unsigned int BoundVertexArrayObjectID;
	 unsigned int BoundShaderProgramID;

	 unsigned int BoundVertexShader;
	 unsigned int BoundFragmentShader;

	 ShaderCompiler compiler;
	 std::vector<Shader> ShaderList;

public:
	GLGraphicsManager();

	void BindVAO(unsigned int VAO);
	void BindShaderProgram(unsigned int VertexShader, unsigned int FragmentShader, ShaderType shaderType);
	void CompileVertexShader(const char* FileName);
	void CompileFragmentShader(const char* FileName);
	void UseShaderProgram(unsigned int ShaderProgram);

	unsigned int GetVAOID() { return BoundVertexArrayObjectID; }
	unsigned int GetVertexShader() { return BoundVertexShader; }
	unsigned int GetFragmentShader() { return BoundFragmentShader; };
	unsigned int GetShaderProgram() { return BoundShaderProgramID; };

	MainShader* GetMainShader()
	{
		Shader* shader = &ShaderList[0];
		MainShader* ptr = static_cast<MainShader*>(shader);
		if (ptr)
		{
			int a = 34;
			
		}
		return ptr;
	}
};
