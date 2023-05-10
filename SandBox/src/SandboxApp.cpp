#include <Poto.h>

 #include "imgui/imgui.h"

class ExampleLayer : public Poto::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Poto::Input::IsKeyPressed(PT_KEY_TAB))
		{
			PT_TRACE("Tab key is pressed (poll)!");
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEnvent(Poto::Event& event) override
	{
		if (event.GetEventType() == Poto::EventType::KeyPressed)
		{
			Poto::KeyPressedEvent& e = (Poto::KeyPressedEvent&)event;
			if (e.GetKeyCode() == PT_KEY_TAB)
			{
				PT_TRACE("Tab key is pressed (event)!");
			}
			PT_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Poto::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Poto::Application* Poto::CreateApplication()
{
	return new Sandbox();
}
