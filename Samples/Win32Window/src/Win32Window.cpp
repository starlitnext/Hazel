#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

// WindowProc ��������
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int main(int argc, char** argv)
{
	// window handle
	HWND hWnd;

	WNDCLASSEX wc;

	::ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = ::GetModuleHandle(NULL);
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = _T("WindowClass1");

	::RegisterClassEx(&wc);

	hWnd = ::CreateWindowEx(0,
		_T("WindowClass1"),
		_T("Hello, World!"),
		WS_OVERLAPPEDWINDOW,
		300, 300, 500, 400,
		NULL,
		NULL,
		::GetModuleHandle(NULL),
		NULL
	);

	::ShowWindow(hWnd, SW_SHOW);

	MSG msg;

	while (::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = ::BeginPaint(hWnd, &ps);
			RECT rect = { 20, 20, 60, 80 };
			HBRUSH brush = (HBRUSH)::GetStockObject(BLACK_BRUSH);
			::FillRect(hdc, &rect, brush);
			::EndPaint(hWnd, &ps);
		} break;
		case WM_DESTROY:
		{
			::PostQuitMessage(0);
			return 0;
		} break;
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}
