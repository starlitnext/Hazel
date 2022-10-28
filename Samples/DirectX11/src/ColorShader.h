#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

struct MatrixBufferType
{
	DirectX::XMMATRIX World;
	DirectX::XMMATRIX View;
	DirectX::XMMATRIX Projection;
};

class ColorShader
{
public:
	bool Initialize(ID3D11Device* d3dDevice, HWND hWnd);
	void ShutDown();
	bool Render(ID3D11DeviceContext* d3dDeviceContext, int indexCount);

private:
	bool InitializeShader(ID3D11Device* d3dDevice, HWND hWnd, WCHAR* vsFilename, WCHAR* psFileName);
	void ShutDownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage);

	bool SetShaderParameters(ID3D11DeviceContext* d3dDeviceCOntext, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix);
	void RenderShader(ID3D11DeviceContext* d3dDeviceCOntext, int indexCount);

private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_Layout = nullptr;
	ID3D11Buffer* m_MatrixBuffer = nullptr;
};
