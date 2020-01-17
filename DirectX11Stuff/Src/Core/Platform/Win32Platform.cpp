#include "PCH.h"
#include "Core/Game/Game.h"
#include "Time/DeltaClock.h"

Game* game = new Game();

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0u;

	switch (msg)
	{
		case WM_CLOSE:
		{
			game->Close();
		} break;

		//Keyboard Messages
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if (!(lParam & 0x40000000 || game->Keyboard.AutorepeatIsEnabled()))
			{
				game->Keyboard.OnKeyPressed(static_cast<u16>(wParam));
			}
		} break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			game->Keyboard.OnKeyReleased(static_cast<u16>(wParam));
		} break;

		case WM_CHAR:
		{
			game->Keyboard.OnChar(static_cast<u16>(wParam));
		} break;

		//Mouse Messages
		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(lParam);
			if (pt.x >= 0 && pt.x < GameSettings::Display::Width && pt.y >= 0 && pt.y < GameSettings::Display::Height)
			{
				game->Mouse.OnMouseMove(pt.x, pt.y);
				if (!game->Mouse.IsInWindow())
				{
					SetCapture(hWnd);
					game->Mouse.OnMouseEnter();
				}
			}
			else
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					game->Mouse.OnMouseMove(pt.x, pt.y);
				}
				else
				{
					ReleaseCapture();
					game->Mouse.OnMouseLeave();
				}
			}
		} break;

		case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			game->Mouse.OnLeftPressed(pt.x, pt.y);
		} break;

		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			game->Mouse.OnRightPressed(pt.x, pt.y);
		} break;

		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			game->Mouse.OnLeftReleased(pt.x, pt.y);
		} break;

		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			game->Mouse.OnRightReleased(pt.x, pt.y);
		} break;

		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				game->Mouse.OnWheelUp(pt.x, pt.y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			{
				game->Mouse.OnWheelDown(pt.x, pt.y);
			}
		} break;

		default:
			Result = DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return(Result);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showCode)
{
	if (!game->Init(WndProc))
	{
		LOG_FATAL("Failed to Initialize Game");
		MessageBox(0u, "Fatal Error Initializing Game. Please See Log and Restart!", "Fatal Error", MB_ICONERROR);

		return(-1);
	}

	MSG Msg = { 0u };
	while (game->IsRunning())
	{
		DeltaClock::BeginTick();

		//@Cleanup Does this windows message loop belong inside or outside of the delta time calculations?
		//Is there a better place for it entirely?
		while (PeekMessage(&Msg, nullptr, 0u, 0u, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		game->HandleInput();
		game->Update();
		game->Render();

		DeltaClock::EndTickk();
	}

	LOG_INFO("Engine Shutting Down After Running For {0} Seconds", Game::Timer.Peek());
	game->Shutdown();

	delete game;
	game = nullptr;

	return(Msg.wParam);
}

//Only used for debug purposes to get a console.
#ifdef WIN32
	#ifdef _DEBUG
	int main()
	{
		WinMain(GetModuleHandle(0u), GetModuleHandle(0u), 0u, 5);
	}
	#endif
#endif