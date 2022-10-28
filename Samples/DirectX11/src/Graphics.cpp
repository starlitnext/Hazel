#include "Graphics.h"
#include "D3DClass.h"

bool Graphics::Initialize(int width, int height, HWND hwnd)
{
	m_D3D = new D3DClass();

	bool result = m_D3D->Initialize(width, height, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_NEAR, SCREEN_DEPTH);
	if (!result)
		return false;

	return true;
}

void Graphics::ShutDown()
{
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

	// Present the rendered scene to the screen
	m_D3D->EndScene();
	return true;
}
