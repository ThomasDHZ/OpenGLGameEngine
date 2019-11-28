#include "ShaderCompiler.h"
#include <iostream>
#include <glad\glad.h>

ShaderCompiler::ShaderCompiler()
{
}

int ShaderCompiler::CompileVertexShader(const char* source)
{
	std::string shaderSource = ReadShaderFile(source);
	const char* shaderSourcePtr = shaderSource.c_str();
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSourcePtr, NULL);
	glCompileShader(vertexShader);
	CheckCompileErrors(vertexShader, "VERTEX");

	return vertexShader;
}

int ShaderCompiler::CompileFragmentShader(const char* source)
{
	std::string shaderSource = ReadShaderFile(source);
	const char* shaderSourcePtr = shaderSource.c_str();
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderSourcePtr, NULL);
	glCompileShader(fragmentShader);
	CheckCompileErrors(fragmentShader, "FRAGMENT");

	return fragmentShader;
}

std::string ShaderCompiler::ReadShaderFile(const char* filePath)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(filePath);
		std::stringstream shaderStream, fShaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderCode;
}

void ShaderCompiler::CheckCompileErrors(int shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}
}