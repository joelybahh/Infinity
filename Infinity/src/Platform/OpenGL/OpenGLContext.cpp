#include "infpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Infinity
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		INF_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		INF_CORE_ASSERT(status, "Failed to initialize Glad!");

		INF_CORE_INFO("");
		INF_CORE_INFO("OpenGL Info:");
		INF_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		INF_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		INF_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		INF_CORE_INFO("");
		
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}