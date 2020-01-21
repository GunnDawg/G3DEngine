#include "PCH.h"
#include "Scene01.h"
#include "Core/Game/Game.h"
#include "Scenes/Scene02.h"

void Scene01::On_enter()
{
	Game::Camera.SetPosition(0.0f, 0.0f, 1.0f);
	Game::Camera.SetProjectionValues(90.0f, (static_cast<float>(GameSettings::Display::Width) / static_cast<float>(GameSettings::Display::Height)), 0.1f, 10.0f);
}

void Scene01::On_exit()
{
	s1.CleanUp();
}

void Scene01::Handle_events()
{
	if (Game::Keyboard.KeyIsPressed(VK_ESCAPE))
	{
		Game::GSM.UnloadAll();
		Game::Close();
	}

	if (Game::Keyboard.KeyIsPressed(VK_RIGHT))
	{
		Game::GSM.Pop();
		std::unique_ptr<Scene02> S2 = std::make_unique<Scene02>();
		Game::GSM.Push(std::move(S2));
	}

	if (Game::Keyboard.KeyIsPressed('A'))
	{
		Game::Camera.AdjustPosition(-0.1f, 0.0f, 0.0f);
	}

	if (Game::Keyboard.KeyIsPressed('D'))
	{
		Game::Camera.AdjustPosition(0.1f, 0.0f, 0.0f);
	}

	if (Game::Keyboard.KeyIsPressed('W'))
	{
		Game::Camera.AdjustPosition(0.0f, 0.0f, 0.1f);
	}

	if (Game::Keyboard.KeyIsPressed('S'))
	{
		Game::Camera.AdjustPosition(0.0f, 0.0f, -0.1f);
	}

	const auto e = Game::Mouse.Read();
	//if (e.GetType() == G3D::Mouse::Event::Type::Move)
	//{
	//	
	//}

	if (e.GetType() == G3D::Mouse::Event::Type::RAW_MOVE)
	{

		Game::Camera.AdjustRotation((float)Game::Mouse.GetDeltaX(), (float)Game::Mouse.GetDeltaY(), 0.0f);
	}

	if (e.GetType() == G3D::Mouse::Event::Type::LPress)
	{
		G3D::LOG_INFO("Left Mouse Button Pressed!");
	}

	if (e.GetType() == G3D::Mouse::Event::Type::RPress)
	{
		G3D::LOG_INFO("Right Mouse Button Pressed!");
	}

	if (e.GetType() == G3D::Mouse::Event::Type::WheelUp)
	{
		G3D::LOG_INFO("Wheel Up!");
	}

	if (e.GetType() == G3D::Mouse::Event::Type::WheelDown)
	{
		G3D::LOG_INFO("Wheel Down!");
	}
}

void Scene01::Update()
{
	s1.Update();
}

void Scene01::Render(G3D::Renderer* renderer)
{
	s1.Render();
}