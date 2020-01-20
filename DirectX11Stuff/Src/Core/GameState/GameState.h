#pragma once

#include "Graphics/Renderer.h"

struct GameState

{
	virtual void On_enter() = 0u;
	virtual void On_exit() = 0u;
	virtual void Handle_events() = 0u;
	virtual void Update() = 0u;
	virtual void Render(G3D::Renderer* renderer) = 0u;
};