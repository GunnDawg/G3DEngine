#pragma once

#include "GameState.h"
#include "Graphics/Renderer.h"

namespace G3D

{
	class GameStateMachine

	{
	public:
		inline void Push(std::unique_ptr<GameState> states)
		{
			//@Speed I haven't tested it yet but I think emplace_back() is faster than push_back() here. Maybe run

			//a test later. Probably not a huge difference either way though.
			mGameStates.emplace_back(std::move(states));
			mGameStates.back()->On_enter();
		}

		inline void Pop()
		{
			if (!mGameStates.empty())
			{
				mGameStates.back()->On_exit();
				mGameStates.pop_back();
			}
		}

		inline void HandleEvents()
		{
			if (!mGameStates.empty())
			{
				mGameStates.back()->Handle_events();
			}
		}

		inline void Update()
		{
			if (!mGameStates.empty())
			{
				mGameStates.back()->Update();
			}
		}

		inline void Render(G3D::Renderer* renderer)
		{
			if (!mGameStates.empty())
			{
				mGameStates.back()->Render(renderer);
			}
		}

		inline void UnloadAll()
		{
			while (!mGameStates.empty())
			{
				Pop();
			}
		}

		std::vector<std::unique_ptr<GameState>> mGameStates;
	};
}