#pragma once
#include <windows.h>


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class D3DClass;
class Camera;
class Model;
class ColorShader;

class Graphics
{
public:
	Graphics() = default;
	~Graphics() = default;

	bool Initialize(int width, int height, HWND hwnd);
	void ShutDown();
	bool Frame();
private:
	bool Render();
private:
	D3DClass* m_D3D = nullptr;
	Camera* m_Camera = nullptr;
	Model* m_Model = nullptr;
	ColorShader* m_ColorShader = nullptr;
};
