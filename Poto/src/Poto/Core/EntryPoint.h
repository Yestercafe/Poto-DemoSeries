#pragma once

#ifdef PT_PLATFORM_WINDOWS

extern Poto::Application* Poto::CreateApplication();

int main(int argc, char** argv)
{
	Poto::Log::Init();

	PT_PROFILE_BEGIN_SESSION("Startup", "PotoProfile-Startup.json");
	auto app = Poto::CreateApplication();
	PT_PROFILE_END_SESSION();

	PT_PROFILE_BEGIN_SESSION("Runtime", "PotoProfile-Runtime.json");
	app->Run();
	PT_PROFILE_END_SESSION();

	PT_PROFILE_BEGIN_SESSION("Startup", "PotoProfile-Shutdown.json");
	delete app;
	PT_PROFILE_END_SESSION();
}

#endif
