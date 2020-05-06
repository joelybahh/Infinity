#pragma once

#ifdef INF_PLATFORM_WINDOWS

extern Infinity::Application* Infinity::CreateApplication();

int main(int argc, char** argv)
{
	printf("Infinity Engine (v%s).\n", ENGINE_VERSION);
	auto app = Infinity::CreateApplication();
	printf("%s Application Loaded.", app->ApplicationName);
	app->Run();
	delete app;
}

#endif