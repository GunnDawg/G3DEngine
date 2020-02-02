#pragma once
#include <spdlog/spdlog.h>

namespace G3D
{
	class Logger
	{
	public:
		static bool Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetFileLogger() { return sFileLogger; }

	private:
		inline static std::shared_ptr<spdlog::logger> sCoreLogger;
		inline static std::shared_ptr<spdlog::logger> sFileLogger;
	};

#ifdef _DEBUG
#define LOG_TRACE(...)	Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)	Logger::GetCoreLogger()->critical(__VA_ARGS__)
#else
#define LOG_TRACE(...)  Logger::GetFileLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)   Logger::GetFileLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)   Logger::GetFileLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)  Logger::GetFileLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)  Logger::GetFileLogger()->critical(__VA_ARGS__)
#endif
}