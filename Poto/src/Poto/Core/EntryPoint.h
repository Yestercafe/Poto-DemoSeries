#pragma once

#ifdef PT_PLATFORM_WINDOWS

extern Poto::Application* Poto::CreateApplication();

int main(int argc, char** argv)
{
	Poto::Log::Init();
	PT_CORE_WARN("Initialize Log");
	int a = 5;
	PT_INFO("Hello! var = {0}", a);

	auto app = Poto::CreateApplication();
	app->Run();
	delete app;
}

#endif
