#include "PCH.h"
#include "Scene01.h"
#include "Core/Game/Game.h"
#include "Scenes/Scene02.h"

void Scene01::On_enter()
{

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

	if (Game::Keyboard.KeyIsPressed('X'))
	{
		LOG_INFO("BREAK!");
	}

	if (Game::Keyboard.KeyIsPressed(VK_RIGHT))
	{
		Game::GSM.Pop();
		std::unique_ptr<Scene02> S2 = std::make_unique<Scene02>();
		Game::GSM.Push(std::move(S2));
	}

	if (Game::Keyboard.KeyIsPressed('D'))
	{
		//LOG_INFO("A Was Pressed!");
		LOG_INFO("{0}", DeltaClock::deltaTime);
	}

	const auto e = Game::Mouse.Read();
	//if (e.GetType() == Mouse::Event::Type::Move)
	//{
	//	LOG_INFO("X:{0} Y:{1}", e.GetPosX(), e.GetPosY());
	//}

	if (e.GetType() == G3D::Mouse::Event::Type::LPress)
	{
		LOG_INFO("Left Mouse Button Pressed!");
	}

	if (e.GetType() == G3D::Mouse::Event::Type::RPress)
	{
		LOG_INFO("Right Mouse Button Pressed!");
	}

	if (e.GetType() == G3D::Mouse::Event::Type::WheelUp)
	{
		LOG_INFO("Wheel Up!");
	}

	if (e.GetType() == G3D::Mouse::Event::Type::WheelDown)
	{
		LOG_INFO("Wheel Down!");
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