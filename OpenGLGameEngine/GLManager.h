#pragma once
#include "ShaderCompiler.h"

class GLManager
{
private:
	 unsigned int BoundVertexArrayObjectID;
	 unsigned int BoundShaderProgramID;

	 unsigned int BoundVertexShader;
	 unsigned int BoundFragmentShader;

	 ShaderCompiler compiler;

public:
	GLManager();

	void BindVAO(unsigned int VAO);
	void BindShaderProgram(unsigned int VertexShader, unsigned int FragmentShader);
	void CompileVertexShader(const char* FileName);
	void CompileFragmentShader(const char* FileName);
	void UseShaderProgram(unsigned int ShaderProgram);

	unsigned int GetVAOID();
	unsigned int GetVertexShader();
	unsigned int GetFragmentShader();
	unsigned int GetShaderProgram();
};

