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

#ifdef INF_ENABLE_ASSERTS
	#define INF_ASSERT(x, ...) { if(!(x)) {INF_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define INF_CORE_ASSERT(x, ...) { if(!(x)) {INF_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define INF_ASSERT(x, ...)
	#define INF_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define INF_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)