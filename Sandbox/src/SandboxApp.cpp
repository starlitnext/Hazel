#include "hzpch.h"
#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() :
		Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("Tab key is pressed!(poll)");
	}

	void OnEvent(Hazel::Event& event) override
	{
		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			HZ_TRACE("{0}(dispatch)", (char)e.GetKeyCode());
		}
	}
};

class SandboxApp : public Hazel::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}

	~SandboxApp()
	{

	}

};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandboxApp;
}
