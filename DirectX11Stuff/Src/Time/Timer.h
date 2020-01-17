#pragma once
#include <chrono>

namespace G3D
{
	class Timer
	{
	public:
		Timer() noexcept;
		float Mark() noexcept;
		inline float Peek() const noexcept
		{
			return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
		}

	private:
		std::chrono::steady_clock::time_point last;
	};
}