#pragma once

#ifdef INF_PLATFORM_WINDOWS
	#ifdef INF_BUILD_DLL
		#define INFINITY_API __declspec(dllexport)
	#else // INF_BUILD_DLL
		#define INFINITY_API __declspec(dllimport)
	#endif
#else
#error Infinity currently only supports windows
#endif

#define BIT(x) (1 << x)