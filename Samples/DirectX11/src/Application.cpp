#include "Application.h"
#include "Input.h"
#include "Graphics.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	s_Instance = this;
}

Application::~Application()
{

}

bool Application::Initialize()
{
	uint32_t screenWidth, screenHeight;
	bool result;

	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api
	InitializeWindows(screenWidth, screenHeight);

	m_Input = new Input();
	m_Input->Initialize();

	m_Graphics = new Graphics();
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hWnd);
	if (!result)
		return false;

	return true;
}

void Application::ShutDown()
{
	delete m_Input;
	m_Input = nullptr;

	m_Graphics->ShutDown();
	delete m_Graphics;
	m_Graphics = nullptr;

	ShutDownWindows();
}

void Application::Run()
{
	MSG msg;
	bool done, result;
	::ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if (!result)
				done = true;
		}
	}
}

LRESULT CALLBACK Application::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			m_Input->KeyDown((uint32_t)wParam);
			return 0;
		}
		case WM_KEYUP:
		{
			m_Input->KeyUp((uint32_t)wParam);
			return 0;
		}
		default:
			return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
}

bool Application::Frame()
{
	bool result;
	if (m_Input->IsKeyDown(VK_ESCAPE))
		return false;

	result = m_Graphics->Frame();
	if (!result)
		return false;

	return true;
}

void Application::InitializeWindows(uint32_t& width, uint32_t& height)
{
	m_hInstance = ::GetModuleHandle(NULL);

	WNDCLASSEX wc;
	::ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = ::LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_ApplicationName;

	// Register the window class.
	::RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	width = (uint32_t)GetSystemMetrics(SM_CXSCREEN);
	height = (uint32_t)GetSystemMetrics(SM_CYSCREEN);

	DEVMODE dmScreenSettings;
	int posX, posY;
	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)width;
		dmScreenSettings.dmPelsHeight = (unsigned long)width;

		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		::ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 1280*720 resolution.
		width = 1280;
		height = 720;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_ApplicationName, m_ApplicationName,
		WS_OVERLAPPEDWINDOW,
		posX, posY, width, height, NULL, NULL, m_hInstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	::ShowWindow(m_hWnd, SW_SHOW);
	::SetForegroundWindow(m_hWnd);
	::SetFocus(m_hWnd);
}

void Application::ShutDownWindows()
{
	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		::ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	::DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	// Remove the application instance.
	::UnregisterClass(m_ApplicationName, m_hInstance);
	m_hInstance = NULL;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
		{
			return Application::Get().MessageHandler(hWnd, message, wParam, lParam);
		}
	}
}
