#include "GLGraphicsManager.h"
#include <glad\glad.h>

GLGraphicsManager::GLGraphicsManager()
{
	BoundVertexArrayObjectID = 0;
	BoundVertexShader = 0;
	BoundFragmentShader = 0;

	compiler = ShaderCompiler();
}

void GLGraphicsManager::BindVAO(unsigned int VAO)
{
	BoundVertexArrayObjectID = VAO;
	glBindVertexArray(VAO);
}

void GLGraphicsManager::BindShaderProgram(unsigned int VertexShader, unsigned int FragmentShader, ShaderType shaderType)
{
	int success;
	char infoLog[512];

	unsigned int NewShaderID = glCreateProgram();
	glAttachShader(BoundShaderProgramID, VertexShader);
	glAttachShader(BoundShaderProgramID, FragmentShader);

	glLinkProgram(BoundShaderProgramID);

	glGetProgramiv(BoundShaderProgramID, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(BoundShaderProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	ShaderList.emplace_back(Shader(NewShaderID, shaderType));

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

void GLGraphicsManager::CompileVertexShader(const char* FileName)
{
	BoundVertexShader = compiler.CompileVertexShader(FileName);
}

void GLGraphicsManager::CompileFragmentShader(const char* FileName)
{
	BoundFragmentShader = compiler.CompileFragmentShader(FileName);
}

void GLGraphicsManager::UseShaderProgram(unsigned int ShaderProgram)
{
	glUseProgram(BoundShaderProgramID);
}