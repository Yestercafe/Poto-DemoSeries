#include <Poto.h>

class ExampleLayer : public Poto::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		PT_INFO("ExampleLayer::Update");
	}

	void OnEnvent(Poto::Event& event) override
	{
		PT_TRACE("{0}", event);
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

