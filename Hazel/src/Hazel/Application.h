#pragma once

#include "Core.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/Window.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
	private: 
		std::unique_ptr<Window> m_Window; 
		bool m_Running = true;
	};

	Application* CreateApplication();
} 