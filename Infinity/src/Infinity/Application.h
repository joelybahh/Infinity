#pragma once

#include "Core.h"

#include "Infinity/Window.h"
#include "Infinity/LayerStack.h"
#include "Infinity/Events/Event.h"
#include "Infinity/Events/ApplicationEvent.h"

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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}