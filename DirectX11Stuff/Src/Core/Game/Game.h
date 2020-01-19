#pragma once

#include "Core/Window/Win32Window.h"
#include "Core/GameState/StateMachine.h"
#include "Graphics/Renderer.h"
#include "Input/Camera.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Time/Timer.h"
#include "Time/DeltaClock.h"
#include "Scenes/Scene01.h"

struct Game
{
	Game() = default;
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	bool Init(const WNDPROC& wndproc);

	//@Speed I don't even know if inlining these actually helps us here, I probably should have benchmarked it FIRST.
	//Maybe do that soon.
	inline void HandleInput() const
	{
		GSM.HandleEvents();
	}

	inline void Update() const
	{
		GSM.Update();
	}

	inline void Render() const
	{
		Renderer->Clear(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		GSM.Render(Renderer);
		Renderer->Present(GameSettings::Display::VSync);
	}

	inline void Shutdown() const
	{
		GSM.UnloadAll();
		Renderer->Shutdown();
		Window->Shutdown();
	}

	//@Cleanup The only reason I'm using a setter method() here is because I plan(nned?) on doing
	//more than just setting isRunning to false. If that never happens then this can be deleted
	//and just make public access to 'isRunning'
	inline static void Close()
	{
		isRunning = false;
	}

	inline bool IsRunning()
	{
		return isRunning;
	}

	G3D::Window* Window = new G3D::Window();
	G3D::Renderer* Renderer = new G3D::Renderer();

	inline static G3D::Camera Camera;
	inline static G3D::Keyboard Keyboard;
	inline static G3D::Mouse Mouse;
	inline static G3D::GameStateMachine GSM;
	inline static G3D::Timer Timer;

private:
	inline static bool isRunning = false;
};