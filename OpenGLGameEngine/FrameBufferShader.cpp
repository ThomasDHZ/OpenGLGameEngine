#include "FrameBufferShader.h"

FrameBufferShader::FrameBufferShader() : Shader()
{
}

FrameBufferShader::FrameBufferShader(int ShaderID, ShaderType shaderType) : Shader(ShaderID, shaderType)
{
	InitializeTextureSampler("screenTexture", 0);
}

FrameBufferShader::~FrameBufferShader()
{
}
