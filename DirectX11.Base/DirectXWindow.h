#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <GLFW/glfw3.h>
#include <wrl.h>

#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32 
#include <GLFW/glfw3native.h>
#include <glm\fwd.hpp>

class DirectXWindow
{
private:
	unsigned int Width;
	unsigned int Height;
	GLFWwindow* Window;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
public:
	DirectXWindow(unsigned int width, unsigned int height, const char* WindowName);
	~DirectXWindow();
	void ClearBuffer(float r, float g, float b);
	void StartFrame();
	void EndFrame();
	void DrawTriangle();
	GLFWwindow* GetWindow() { return Window; }
};

