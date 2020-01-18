#pragma once
#include <chrono>

namespace G3D
{

	class Benchmarker
	{
	public:
		Benchmarker()
		{
			StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		~Benchmarker()
		{
			Stop();
		}

		void Stop()
		{
			auto EndTimePoint = std::chrono::high_resolution_clock::now();
			auto Start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTimePoint).time_since_epoch().count();
			auto End = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch().count();
			auto Duration = End - Start;
			double ms = Duration * 0.001;
			time_t = ms;

			//@Debug uncomment this if for some reason you want the benchmark timer to print when stop is called.
			//Right now we're just storing it in time_t to make use of it in the logger. Just grab it with Peek() for now.
			//printf("%f ms\n", ms);
		}

		inline double Peek()
		{
			return time_t;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> StartTimePoint;
		double time_t = 0.0;
	};
}