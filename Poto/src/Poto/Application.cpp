#include "ptpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Log.h"

namespace Poto
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		PT_TRACE(e);

		while (true);
	}

}
