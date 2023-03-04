#pragma once

#include "Core.h"
#include "Window.h"
#include "Poto/LayerStack.h"
#include "Poto/Events/Event.h"
#include "Poto/Events/ApplicationEvent.h"

namespace Poto
{
	class POTO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
