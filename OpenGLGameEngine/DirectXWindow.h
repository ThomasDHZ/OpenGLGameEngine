#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32 
#include <GLFW/glfw3native.h>
#include <glm\fwd.hpp>

class DirectXWindow
{
private:
	GLFWwindow* Window;
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
public:
	DirectXWindow(unsigned int width, unsigned int height, const char* WindowName);
	~DirectXWindow();
	void ClearBuffer(float r, float g, float b);
	void EndFrame();
	GLFWwindow* GetWindow() { return Window; }
};

