#include "infpch.h"
#include "Application.h"

#include "Infinity/Log.h"

#include <Glad/glad.h>

namespace Infinity
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application(const char* appName) : ApplicationName(appName)
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
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
		EventDispacher dispacher(e);
		dispacher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClose));

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