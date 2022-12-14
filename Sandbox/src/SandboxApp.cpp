#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Sandbox2D.h"


class SandboxApp : public Hazel::Application
{
public:
	SandboxApp()
	{
		PushLayer(new Sandbox2D());
	}

	~SandboxApp()
	{

	}

};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandboxApp;
}
