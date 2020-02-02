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

		inline void EnableCursor()
		{
			mCursorEnabled = true;
			ShowCursor();
			UnlockCursor();
		}

		inline void DisableCursor()
		{
			mCursorEnabled = false;
			HideCursor();
			LockCursor();
		}

	private:
		inline void HideCursor()
		{
			while (::ShowCursor(FALSE) >= 0);
		}

		inline void ShowCursor()
		{
			while (::ShowCursor(TRUE) < 0);
		}

		inline void LockCursor()
		{
			RECT rect;
			GetClientRect(hWND, &rect);
			MapWindowPoints(hWND, nullptr, reinterpret_cast<POINT*>(&rect), 2);
			ClipCursor(&rect);
		}

		inline void UnlockCursor()
		{
			ClipCursor(nullptr);
		}

		HWND hWND;
		WNDCLASSEX WC;

		bool mCursorEnabled = false;
	};
}