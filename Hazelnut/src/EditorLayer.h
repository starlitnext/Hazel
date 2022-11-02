#pragma once

#include "Hazel.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Hazel {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		Ref<Texture2D> m_CheckboardTexture;

		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewportSize = { 0, 0 };

		Ref<Scene> m_ActiveScene;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_ViewportFocused = false;
		bool m_ViewPortHovered = false;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}
