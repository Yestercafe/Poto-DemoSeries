#include <Poto.h>
#include <Poto/Core/EntryPoint.h>

#include "GameLayer.h"

class Sandbox : public Poto::Application
{
public:
	Sandbox()
	{
		PushLayer(new GameLayer());
	}

	~Sandbox()
	{
		
	}
};

Poto::Application* Poto::CreateApplication()
{
	return new Sandbox();
}
