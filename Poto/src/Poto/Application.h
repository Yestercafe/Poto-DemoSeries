#pragma once

#include "Core.h"
#include "Window.h"

namespace Poto
{
	class POTO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
