#include "PCH.h"
#include "Scene02.h"
#include "Scene01.h"
#include "Core/Game/Game.h"

void Scene02::On_enter()
{

}

void Scene02::On_exit()
{

}

void Scene02::Handle_events()
{
	if (Game::Keyboard.KeyIsPressed(VK_ESCAPE))
	{
		Game::Close();
	}

	if (Game::Keyboard.KeyIsPressed('X'))
	{
		LOG_INFO("BREAK!");
	}

	if (Game::Keyboard.KeyIsPressed(VK_LEFT))
	{
		Game::GSM.Pop();
		std::unique_ptr<Scene01> S1 = std::make_unique<Scene01>();
		Game::GSM.Push(std::move(S1));
	}
}

void Scene02::Update()
{

}

void Scene02::Render(G3D::Renderer* renderer)
{
	renderer->Clear(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
}