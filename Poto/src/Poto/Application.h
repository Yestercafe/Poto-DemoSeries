#pragma once

#include "Core.h"
#include "Window.h"
#include "Poto/LayerStack.h"
#include "Poto/Events/Event.h"
#include "Poto/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

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

		inline Window& GetWindow() const { return *m_window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
