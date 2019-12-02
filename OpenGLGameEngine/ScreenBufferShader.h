#pragma once
#include "Shader.h"
class ScreenBufferShader :public Shader
{
public:
	ScreenBufferShader();
	ScreenBufferShader(int ShaderID, ShaderType shaderType);
	~ScreenBufferShader();
};

