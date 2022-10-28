#pragma once

#include <d3d11.h>
#include <directxmath.h>

struct VertexType
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 color;
};

class Model
{
public:
	bool Initialize(ID3D11Device* d3dDevice);
	void ShutDown();
	void Render(ID3D11DeviceContext* d3dDeviceContext);

	int GetIndexCount();
private:
	bool InitializeBuffers(ID3D11Device* d3dDevice);
	void ShutDownBuffers();
	void RenderBuffers(ID3D11DeviceContext* d3dDeviceContext);
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
	int m_VertexCount = 0;
	int m_IndexCount = 0;
};
