#pragma once

#ifdef PT_PLATFORM_WINDOWS
	#ifdef PT_BUILD_DLL
		#define POTO_API _declspec(dllexport)
	#else
		#define POTO_API _declspec(dllimport)
	#endif
#else
	#error Poto only supports Windows
#endif

#define BIT(x) (1 << x)