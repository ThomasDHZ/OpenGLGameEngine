#include "GLManager.h"
#include <glad\glad.h>

GLManager::GLManager()
{
	BoundVertexArrayObjectID = 0;
	BoundVertexShader = 0;
	BoundFragmentShader = 0;

	compiler = ShaderCompiler();
}

void GLManager::BindVAO(unsigned int VAO)
{
	BoundVertexArrayObjectID = VAO;
	glBindVertexArray(VAO);
}

void GLManager::BindShaderProgram(unsigned int VertexShader, unsigned int FragmentShader)
{
	int success;
	char infoLog[512];

	ShaderProgramID = glCreateProgram();
	glAttachShader(ShaderProgramID, VertexShader);
	glAttachShader(ShaderProgramID, FragmentShader);

	glLinkProgram(ShaderProgramID);

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

void GLManager::CompileVertexShader(const char* FileName)
{
	BoundVertexShader = compiler.CompileVertexShader(FileName);
}

void GLManager::CompileFragmentShader(const char* FileName)
{
	BoundFragmentShader = compiler.CompileFragmentShader(FileName);
}

void GLManager::UseShaderProgram(unsigned int ShaderProgram)
{
	glUseProgram(ShaderProgramID);
}

unsigned int GLManager::GetVAOID()
{
	return BoundVertexArrayObjectID;
}

unsigned int GLManager::GetVertexShader()
{
	return BoundVertexShader;
}

unsigned int GLManager::GetFragmentShader()
{
	return BoundFragmentShader;
}

unsigned int GLManager::GetShaderProgram()
{
	return ShaderProgramID;
}
