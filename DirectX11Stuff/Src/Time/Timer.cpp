#include "PCH.h"
#include "Timer.h"

G3D::Timer::Timer() noexcept
{
	last = std::chrono::steady_clock::now();
}

float G3D::Timer::Mark() noexcept
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}