#include "Camera.h"

void Camera::Render()
{
	DirectX::XMVECTOR position{m_Position.x, m_Position.y, m_Position.z};
	
	DirectX::XMVECTOR up{ 0.0f, 1.0f, 0.0f };
	DirectX::XMVECTOR lookAt{ 0.0f, 0.0f, 1.0f };

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	float yaw = m_Rotation.x * 0.0174532925f;
	float pitch = m_Rotation.y * 0.0174532925f;
	float roll = m_Rotation.z * 0.0174532925f;
	
	// Create the rotation matrix from the yaw, pitch, roll values.
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transfrom the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = DirectX::XMVector3TransformCoord(lookAt, rotationMatrix);
	up = DirectX::XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = DirectX::XMVectorAdd(position, lookAt);

	// Finally create the view matrhx from the three updated vectors.
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(position, lookAt, up);
}
