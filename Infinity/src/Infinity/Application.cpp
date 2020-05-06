#include "infpch.h"
#include "Application.h"

#include "Infinity/Events/ApplicationEvent.h"
#include "Infinity/Log.h"

#include <GLFW/glfw3.h>

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

	void Application::OnEvent(Event& e)
	{
		INF_CORE_INFO("{0}", e);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}