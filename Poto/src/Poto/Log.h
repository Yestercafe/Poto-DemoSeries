#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Poto
{
	class POTO_API Log
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
#define PT_CORE_TRACE(...)  ::Poto::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PT_CORE_INFO(...)   ::Poto::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PT_CORE_WARN(...)   ::Poto::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PT_CORE_ERROR(...)  ::Poto::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PT_CORE_FATAL(...)  ::Poto::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define PT_TRACE(...)	    ::Poto::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PT_INFO(...)	    ::Poto::Log::GetClientLogger()->info(__VA_ARGS__)
#define PT_WARN(...)	    ::Poto::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PT_ERROR(...)	    ::Poto::Log::GetClientLogger()->error(__VA_ARGS__)
#define PT_FATAL(...)	    ::Poto::Log::GetClientLogger()->fatal(__VA_ARGS__)

// if dist build
#define PT_CORE_INFO
