#include <Poto.h>

class Sandbox : public Poto::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Poto::Application* Poto::CreateApplication()
{
	return new Sandbox();
}

