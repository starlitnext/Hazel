#pragma once

#include <stdint.h>
#include <windows.h>
#include <memory>
#include <string>
#include <tchar.h>

class Input;
class Graphics;

class Application
{
public:
	Application();
	~Application();

	bool Initialize();
	void ShutDown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	inline static Application& Get() { return *s_Instance; }
private:
	bool Frame();
	void InitializeWindows(uint32_t&, uint32_t&);
	void ShutDownWindows();

private:
	// TODO 指定窗口名
	LPCWSTR m_ApplicationName = L"Engine";
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	Input* m_Input;
	Graphics* m_Graphics;

	static Application* s_Instance;
};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
