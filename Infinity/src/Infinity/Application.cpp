#include "infpch.h"
#include "Application.h"

#include "Infinity/Log.h"

#include <Glad/glad.h>

namespace Infinity
{
	
    Application* Application::s_Instance = nullptr;

	Application::Application(const char* appName) : ApplicationName(appName)
	{
		INF_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(INF_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispacher(e);
		dispacher.Dispatch<WindowClosedEvent>(INF_BIND_EVENT_FN(Application::OnWindowClose));

		// For events, we want to iterate down the stack.
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			// If this layer handles the event, don't continue down the stack.
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Can use the range based for loop because we implemented a begin and end
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowClosedEvent & e)
	{
		m_Running = false;
		return true;
	}
}