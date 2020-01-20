#pragma once

#include "Core/GameState/GameState.h"
#include "Graphics/Renderer.h"
#include "Graphics/Geometry/Square.h"

class Scene01 : public GameState

{
public:
	void On_enter() override;
	void On_exit() override;
	void Handle_events() override;
	void Update() override;
	void Render(G3D::Renderer* renderer) override;

private:
	Square s1;
};