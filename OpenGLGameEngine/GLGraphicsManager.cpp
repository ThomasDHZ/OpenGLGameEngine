#include "GLGraphicsManager.h"
#include <glad\glad.h>

GLGraphicsManager::GLGraphicsManager()
{
	BoundVertexArrayObjectID = 0;
	BoundVertexShader = 0;
	BoundFragmentShader = 0;

	compiler = ShaderCompiler();
}

void GLGraphicsManager::SetShaderBoolValue(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(BoundShaderProgramID, name.c_str()), (int)value);
}

void GLGraphicsManager::SetShaderIntValue(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(BoundShaderProgramID, name.c_str()), value);
}

void GLGraphicsManager::SetShaderFloatValue(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(BoundShaderProgramID, name.c_str()), value);
}

void GLGraphicsManager::SetShaderVec2Value(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(BoundShaderProgramID, name.c_str()), x, y);
}

void GLGraphicsManager::SetShaderVec3Value(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(BoundShaderProgramID, name.c_str()), x, y, z);
}

void GLGraphicsManager::SetShaderVec4Value(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(BoundShaderProgramID, name.c_str()), x, y, z, w);
}

void GLGraphicsManager::SetShaderMat2Value(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(BoundShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GLGraphicsManager::SetShaderMat3Value(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(BoundShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GLGraphicsManager::SetShaderMat4Value(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(BoundShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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