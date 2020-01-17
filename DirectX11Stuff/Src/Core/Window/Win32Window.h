#pragma once

namespace G3D
{
	class Window
	{
	public:
		bool Init(const WNDPROC& wndproc);
		bool Create();
		bool Create(u16 w, u16 h);
		inline void Shutdown()
		{
			if (hWND)
			{
				DestroyWindow(hWND);
				hWND = nullptr;
			}
			UnregisterClass(WC.lpszClassName, GetModuleHandle(0u));
		}

	private:
		HWND hWND;
		WNDCLASSEX WC;
	};
}