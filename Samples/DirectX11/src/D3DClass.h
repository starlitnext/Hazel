#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <directxmath.h>

class D3DClass
{
public:
	bool Initialize(int width, int height, bool vsync, HWND hWnd, bool fullscreen, float zNear, float zFar);
	void ShutDown();

	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	DirectX::XMMATRIX& GetProjectionMatrix() { return m_ProjectionMatrix; }
	DirectX::XMMATRIX& GetWorldMatrix() { return m_WorldMatrix; }
	DirectX::XMMATRIX& GetOrthoMatrix() { return m_OrthoMatrix; }

	void GetVideoCardInfo(char*, int&);
private:
	bool m_VsyncEnabled;
	int m_VideoCardMemory;
	char m_VideoCardDescription[128];
	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11Device* m_Device = nullptr;
	ID3D11DeviceContext* m_DeviceContext = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11Texture2D* m_DepthStencilBuffer = nullptr;
	ID3D11DepthStencilState* m_DepthStencilState = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
	ID3D11RasterizerState* m_RasterState = nullptr;

	DirectX::XMMATRIX m_ProjectionMatrix;
	DirectX::XMMATRIX m_WorldMatrix;
	DirectX::XMMATRIX m_OrthoMatrix;
};
