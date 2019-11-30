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

	BoundShaderProgramID = glCreateProgram();
	glAttachShader(BoundShaderProgramID, VertexShader);
	glAttachShader(BoundShaderProgramID, FragmentShader);

	glLinkProgram(BoundShaderProgramID);

	glGetProgramiv(BoundShaderProgramID, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(BoundShaderProgramID, 512, NULL, infoLog);
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
	glUseProgram(BoundShaderProgramID);
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
	return BoundShaderProgramID;
}
