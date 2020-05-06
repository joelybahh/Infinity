#include "infpch.h"
#include "Application.h"

#include "Infinity/Events/ApplicationEvent.h"
#include "Infinity/Log.h"

namespace Infinity
{
	Application::Application(const char* appName) : ApplicationName(appName)
	{ }

	Application::~Application()
	{

	}

	void Application::Run()
	{

		while (true);
	}
}