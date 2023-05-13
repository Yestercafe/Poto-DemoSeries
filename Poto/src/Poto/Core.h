#pragma once

#include <memory>

#ifdef PT_PLATFORM_WINDOWS
#if PT_DYNAMIC_LINK
	#ifdef PT_BUILD_DLL
		#define POTO_API _declspec(dllexport)
	#else
		#define POTO_API _declspec(dllimport)
	#endif
#else
	#define POTO_API
#endif

#else
	#error Poto only supports Windows
#endif

#ifdef PT_DEBUG
	#define PT_ENABLE_ASSERTS
#endif

#ifdef PT_ENABLE_ASSERTS
	#define PT_ASSERT(x, ...) {if(!(x)) { PT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PT_CORE_ASSERT(x, ...) { if(!(x)) { PT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define PT_ASSERT(x, ...)
	#define PT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define PT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Poto
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
