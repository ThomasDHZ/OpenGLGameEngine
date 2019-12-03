#include "GLGraphicsManager.h"
#include <glad\glad.h>
#include "ShaderTypeEnum.h"

GLGraphicsManager::GLGraphicsManager()
{
	BoundVertexArrayObjectID = 0;
	BoundVertexShader = 0;
	BoundFragmentShader = 0;

	compiler = ShaderCompiler();
}

GLGraphicsManager::~GLGraphicsManager()
{
	for (Texture texture : TextureList)
	{
		texture.ReleaseTexture();
	}
}

void GLGraphicsManager::AddTexture(Texture texture)
{
	TextureList.emplace_back(texture);
}

void GLGraphicsManager::BindVAO(unsigned int VAO)
{
	BoundVertexArrayObjectID = VAO;
	glBindVertexArray(VAO);
}

void GLGraphicsManager::BindShaderProgram(unsigned int VertexShader, unsigned int FragmentShader)
{
	int success;
	char infoLog[512];

	unsigned int ShaderProgramID = glCreateProgram();
	glAttachShader(ShaderProgramID, VertexShader);
	glAttachShader(ShaderProgramID, FragmentShader);

	glLinkProgram(ShaderProgramID);

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	ShaderList.emplace_back(Shader(ShaderProgramID, ShaderType::sMain));

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
	glUseProgram(ShaderProgram);
}