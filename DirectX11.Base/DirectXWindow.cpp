#include "DirectXWindow.h"
#include <iostream>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

DirectXWindow::DirectXWindow(unsigned int width, unsigned int height, const char* WindowName)
{
	Width = width;
	Height = height;

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	Window = glfwCreateWindow(width, height, WindowName, nullptr, nullptr);

	glfwMakeContextCurrent(Window);

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = glfwGetWin32Window(Window);
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);

	ID3D11Resource* pBackBuffer = nullptr;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
	pBackBuffer->Release();
}

DirectXWindow::~DirectXWindow()
{
	glfwDestroyWindow(Window);
	glfwTerminate();
}

void DirectXWindow::ClearBuffer(float r, float g, float b)
{
	const float color[] = { r, g,b,1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
}

void DirectXWindow::StartFrame()
{
	glfwPollEvents();
}

void DirectXWindow::EndFrame()
{
	pSwap->Present(1u, 0u);
}

void DirectXWindow::DrawTriangle()
{
	namespace wrl = Microsoft::WRL;

	struct DXVertex
	{
		struct
		{
			float x;
			float y;
		} pos;
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		} color;
	};

	const DXVertex vertices[] =
	{
		{0.0f, 0.5f, 255, 255, 0, 0},
		{0.5f, -0.5f, 0, 255, 0, 0},
		{-0.5f, -0.5f, 0, 0, 255, 0}
	};

	wrl::ComPtr<ID3D11Buffer> VertexBuffer;
	
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(DXVertex);
	
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;

	pDevice->CreateBuffer(&bd, &sd, &VertexBuffer);

	const unsigned int stride = sizeof(DXVertex);
	const unsigned int offset = 0u;

	pContext->IASetVertexBuffers(0u, 1u, VertexBuffer.GetAddressOf(), &stride, &offset);

	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;

	D3DReadFileToBlob(L"C:\\Users\\ZZT\\source\\repos\\OpenGLGameEngine\\DirectX11.Base\\PixelShader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);

	D3DReadFileToBlob(L"C:\\Users\\ZZT\\source\\repos\\OpenGLGameEngine\\DirectX11.Base\\VertexShader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	pContext->VSSetShader(pVertexShader.Get(), nullptr, 0);

	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 8u, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	pDevice->CreateInputLayout(ied, (unsigned int)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

	pContext->IASetInputLayout(pInputLayout.Get());

	pContext->OMSetRenderTargets( 1u, pTarget.GetAddressOf(), nullptr);

	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1u, &vp);

	pContext->Draw( (unsigned int)std::size(vertices), 0u);
}
