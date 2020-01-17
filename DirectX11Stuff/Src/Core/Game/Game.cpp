#include "PCH.h"
#include "Core/Game/Game.h"
#include <DirectXMath.h>

Game::~Game()
{
	if (Window)
	{
		delete Window;
		Window = nullptr;
	}

	if (Renderer)
	{
		delete Renderer;
		Renderer = nullptr;
	}
}

bool Game::Init(const WNDPROC& wndproc)
{
	Benchmarker InitializTimer;
	if (!Logger::Init())
	{
		//We can't really log a message if the logger fails, so we'll let windows handle it for now, and use a message box.
		MessageBox(0u, "Fatal Error Initializing Logging System!", "Fatal Error", MB_ICONERROR);
		return(false);
	}

	if (!Window->Init(wndproc))
	{
		LOG_FATAL("Failed to Initialize Window");
		return(false);
	}

	if (!Window->Create())
	{
		LOG_FATAL("Failed to Create Window!");
		return(false);
	}

	if (!Renderer->Init())
	{
		LOG_FATAL("Failed to Initialize Renderer");
		return(false);
	}

	DeltaClock::Init();

	std::unique_ptr<GameState> S1 = std::make_unique<Scene01>();
	GSM.Push(std::move(S1));

	isRunning = true;

	InitializTimer.Stop();
	LOG_INFO("Engine Successfully Initialized after {0} ms, or {1} seconds", InitializTimer.Peek(), (InitializTimer.Peek() / 1000));

	return(true);
}