#pragma once

#include "Hazel.h"

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
		OrthographicCameraController m_CameraController;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		Ref<Texture2D> m_CheckboardTexture;

		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewportSize = { 0, 0 };

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;

		bool m_ViewportFocused = false;
		bool m_ViewPortHovered = false;
	};

}
