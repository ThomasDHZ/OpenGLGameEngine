#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderCompiler
{
private:
	std::string ReadShaderFile(const char* filePath);
	void CheckCompileErrors(int shader, std::string type);
public:
	ShaderCompiler();
	int CompileVertexShader(const char* source);
	int CompileFragmentShader(const char* source);
};

