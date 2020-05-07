#include <Infinity.h>

class ExampleLayer : public Infinity::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		INF_INFO("ExampleLayer::Update");
	}

	void OnEvent(Infinity::Event& event) override
	{
		INF_TRACE("{0}", event);
	}
};

class Sandbox : public Infinity::Application
{
public:
	Sandbox(const char* appName) : Application(appName) 
	{ 
		PushLayer(new ExampleLayer());
		PushOverlay(new Infinity::ImGuiLayer());
	}
	Sandbox(const char* appName, const char* appVersion) : Application(appName) {
		ApplicationVersion = appVersion;
		INF_INFO("{0} {1}", ApplicationName, ApplicationVersion);

		PushLayer(new ExampleLayer());
		PushOverlay(new Infinity::ImGuiLayer());
	}
	~Sandbox() { }
};

Infinity::Application* Infinity::CreateApplication()
{
	return new Sandbox("Sandbox", "1.0.0");
}