#pragma once
#include "Core/GameState/GameState.h"
#include "Graphics/Renderer.h"

class Scene02 : public GameState
{
public:
	void On_enter() override;
	void On_exit() override;
	void Handle_events() override;
	void Update() override;
	void Render(G3D::Renderer* renderer) override;

private:

};