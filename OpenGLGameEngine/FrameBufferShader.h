#pragma once
#include "Shader.h"
class FrameBufferShader :public Shader
{
public:
	FrameBufferShader();
	FrameBufferShader(int ShaderID, ShaderType shaderType);
	~FrameBufferShader();
};

