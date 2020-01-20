#include "PCH.h"
#include "Core/Window/Win32Window.h"

bool G3D::Window::Init(const WNDPROC& wndproc)
{
	ZeroMemory(&WC, sizeof(WNDCLASSEX));
	WC.cbSize = sizeof(WNDCLASSEX);
	WC.hbrBackground = HBRUSH(COLOR_WINDOW);
	WC.hCursor = LoadCursor(0u, IDC_ARROW);
	WC.hInstance = GetModuleHandle(0u);
	WC.lpfnWndProc = wndproc;
	WC.lpszClassName = "WindowClass";
	WC.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClassEx(&WC))
	{
		LOG_FATAL("Failed to Register Window Class");
		return(false);
	}

	//Get users current screen resolution and set the window to that size. Although something in DirectX is making use of this

	//value in GameSettings.h, which means we still have to set a default value there, which is annoying.
	GameSettings::Display::Width = GetSystemMetrics(SM_CXSCREEN);
	GameSettings::Display::Height = GetSystemMetrics(SM_CYSCREEN);

	return(true);
}

bool G3D::Window::Create()
{
	hWND = CreateWindowEx(
		0u,
		WC.lpszClassName,
		"DirectX 11 Stuff",
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GameSettings::Display::Width,
		GameSettings::Display::Height,
		0u,
		0u,
		GetModuleHandle(0u),
		0u);

	if (!hWND)
	{
		return(false);
	}

	return(true);
}

bool G3D::Window::Create(u16 w, u16 h)
{
	GameSettings::Display::Width = w;
	GameSettings::Display::Height = h;

	hWND = CreateWindowEx(
		0u,
		WC.lpszClassName,
		"DirectX 11 Stuff",
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GameSettings::Display::Width,
		GameSettings::Display::Height,
		0u,
		0u,
		GetModuleHandle(0u),
		0u);

	if (!hWND)
	{
		return(false);
	}

	return(true);
}