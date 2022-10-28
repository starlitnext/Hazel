#pragma once

#include <DirectXMath.h>

class Camera
{
public:
	void SetPosition(const DirectX::XMFLOAT3& pos) { m_Position = pos; }
	void SetRotation(const DirectX::XMFLOAT3& rot) { m_Rotation = rot; }

	DirectX::XMFLOAT3& GetPosition() { return m_Position; }
	DirectX::XMFLOAT3& GetRotation() { return m_Rotation; }
	DirectX::XMMATRIX& GetViewMatrix() { return m_ViewMatrix; }

	void Render();
private:
	DirectX::XMFLOAT3 m_Position;
	DirectX::XMFLOAT3 m_Rotation;
	DirectX::XMMATRIX m_ViewMatrix;
};
