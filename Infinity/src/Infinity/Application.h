#pragma once

#include "Core.h"

namespace Infinity
{
#define ENGINE_VERSION "0.0.1"

	class INFINITY_API Application
	{
	public:
		const char* ApplicationName;
		const char* ApplicationVersion;
	public:
		Application(const char* appName);
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}