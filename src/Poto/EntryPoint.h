#pragma once

#ifdef PT_PLATFORM_WINDOWS

extern Poto::Application* Poto::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Poto::CreateApplication();
	app->Run();
	delete app;
}

#endif
