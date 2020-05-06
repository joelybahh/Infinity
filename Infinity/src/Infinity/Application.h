#pragma once

#include "Core.h"
#include "Window.h"

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

		void OnEvent(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}