#pragma once

#ifdef INF_PLATFORM_WINDOWS

extern Infinity::Application* Infinity::CreateApplication();

int main(int argc, char** argv)
{
	Infinity::Log::Init();
	INF_CORE_INFO("Infinity Engine {0}", ENGINE_VERSION);
	auto app = Infinity::CreateApplication();
	app->Run();
	delete app;
	//printf("Infinity Engine (v%s).\n", ENGINE_VERSION);
	//printf("%s Application Loaded.", app->ApplicationName);
}

#endif