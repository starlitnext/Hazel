#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "GameLayer.h"

class SandboxApp : public Hazel::Application
{
public:
	SandboxApp()
	{
		PushLayer(new GameLayer());
	}

	~SandboxApp()
	{

	}

};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandboxApp;
}
