#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Infinity
{
	class INFINITY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define INF_CORE_TRACE(...)     ::Infinity::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define INF_CORE_WARN(...)      ::Infinity::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define INF_CORE_INFO(...)      ::Infinity::Log::GetCoreLogger()->info(__VA_ARGS__)
#define INF_CORE_ERROR(...)     ::Infinity::Log::GetCoreLogger()->error(__VA_ARGS__)
#define INF_CORE_FATAL(...)     ::Infinity::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define INF_TRACE(...)          ::Infinity::Log::GetClientLogger()->trace(__VA_ARGS__)
#define INF_WARN(...)           ::Infinity::Log::GetClientLogger()->warn(__VA_ARGS__)
#define INF_INFO(...)           ::Infinity::Log::GetClientLogger()->info(__VA_ARGS__)
#define INF_ERROR(...)          ::Infinity::Log::GetClientLogger()->error(__VA_ARGS__)
#define INF_FATAL(...)          ::Infinity::Log::GetClientLogger()->critical(__VA_ARGS__)

