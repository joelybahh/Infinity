#include <Infinity.h>

class Sandbox : public Infinity::Application
{
public:
	Sandbox(const char* appName) : Application(appName) { }
	Sandbox(const char* appName, const char* appVersion) : Application(appName) {
		ApplicationVersion = appVersion;
		INF_INFO("{0} {1}", ApplicationName, ApplicationVersion);
	}
	~Sandbox() { }
};

Infinity::Application* Infinity::CreateApplication()
{
	return new Sandbox("Sandbox", "1.0.0");
}