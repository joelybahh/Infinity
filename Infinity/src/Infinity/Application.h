#pragma once

#include "Core.h"

#include "Infinity/Window.h"
#include "Infinity/LayerStack.h"
#include "Infinity/Events/Event.h"
#include "Infinity/Events/ApplicationEvent.h"

#include "Infinity/ImGui/ImGuiLayer.h"

#include "Infinity/Renderer/Shader.h"
#include "Infinity/Renderer/Buffer.h"

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
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		UINT m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer>  m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}