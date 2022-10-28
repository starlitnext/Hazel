#include "Graphics.h"
#include "D3DClass.h"
#include "Camera.h"
#include "Model.h"
#include "ColorShader.h"

#include <iostream>

bool Graphics::Initialize(int width, int height, HWND hwnd)
{
	bool result;

	m_D3D = new D3DClass();
	result = m_D3D->Initialize(width, height, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_NEAR, SCREEN_DEPTH);
	if (!result)
	{
		std::cerr << "D3DClass Initialize failed!" << std::endl;
		return false;
	}

	m_Camera = new Camera();
	// Set the initial position of the camera
	m_Camera->SetPosition({ 0.0f, 0.0f, -10.0f });

	m_Model = new Model();
	result = m_Model->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		std::cerr << "Model Initialize failed!" << std::endl;
		return false;
	}

	m_ColorShader = new ColorShader();
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		std::cerr << "Color Shader Initialize failed!" << std::endl;
		return false;
	}

	return true;
}

void Graphics::ShutDown()
{
	if (m_ColorShader)
	{
		m_ColorShader->ShutDown();
		delete m_ColorShader;
		m_ColorShader = nullptr;
	}

	if (m_Model)
	{
		m_Model->ShutDown();
		delete m_Model;
		m_Model = nullptr;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = nullptr;
	}

	if (m_D3D)
	{
		m_D3D->ShutDown();
		delete m_D3D;
		m_D3D = nullptr;
	}
}

bool Graphics::Frame()
{
	bool result = Render();
	if (!result)
		return false;

	return true;
}

bool Graphics::Render()
{
	// Clear the buffers to begin the scene
	m_D3D->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	// Gemerate the view matrix based on the camera's position.
	// m_Camera->Render();

	// Get the World, View, Projection matrices from the camera and d3d object.
	/*
	auto viewMatrix = m_Camera->GetViewMatrix();
	auto worldMatrix = m_D3D->GetWorldMatrix();
	auto projectionMatrix = m_D3D->GetProjectionMatrix();
	*/

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	bool result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount());
	if (!result)
		return false;

	// Present the rendered scene to the screen
	m_D3D->EndScene();
	return true;
}
