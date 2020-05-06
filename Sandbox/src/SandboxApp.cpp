#include <Infinity.h>

class Sandbox : public Infinity::Application
{
public:
	Sandbox(const char* appName) : Application(appName) { }
	~Sandbox() { }
};

Infinity::Application* Infinity::CreateApplication()
{
	return new Sandbox("Sandbox");
}