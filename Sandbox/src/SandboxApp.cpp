#include <Infinity.h>

#include "imgui/imgui.h"

class ExampleLayer : public Infinity::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		//INF_INFO("ExampleLayer::Update");
	
		if (Infinity::Input::IsKeyPressed(INF_KEY_TAB))
			INF_TRACE("Tab key is pressed");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Infinity::Event& event) override
	{
		//INF_TRACE("{0}", event);
		if (event.GetEventType() == Infinity::EventType::KeyPressed)
		{
			Infinity::KeyPressedEvent& e = (Infinity::KeyPressedEvent&)event;
			INF_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Infinity::Application
{
public:
	Sandbox(const char* appName) : Application(appName) 
	{ 
		PushLayer(new ExampleLayer());
	}
	Sandbox(const char* appName, const char* appVersion) : Application(appName) {
		ApplicationVersion = appVersion;
		INF_INFO("{0} {1}", ApplicationName, ApplicationVersion);

		PushLayer(new ExampleLayer());
	}
	~Sandbox() { }
};

Infinity::Application* Infinity::CreateApplication()
{
	return new Sandbox("Sandbox", "1.0.0");
}