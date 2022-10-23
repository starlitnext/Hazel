#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel {

	class HazelEditorApp : public Application
	{
	public:
		HazelEditorApp(const std::string& name) :
			Application(name)
		{
			PushLayer(new EditorLayer());
		}

		~HazelEditorApp()
		{

		}

	};

	Application* CreateApplication()
	{
		return new HazelEditorApp("Hazel Editor");
	}

}
