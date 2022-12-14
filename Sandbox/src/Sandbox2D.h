#pragma once

#include "Hazel.h"
#include "ParticleSystem.h"

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Hazel::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Hazel::Event& event) override;
private:
	Hazel::OrthographicCameraController m_CameraController;

	Hazel::Ref<Hazel::Shader> m_FlatColorShader;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	Hazel::Ref<Hazel::Texture2D> m_CheckboardTexture;

	Hazel::Ref<Hazel::Texture2D> m_SpriteSheet;
	Hazel::Ref<Hazel::SubTexture2D> m_TextureStairs;
	Hazel::Ref<Hazel::SubTexture2D> m_TextureBarrel;
	Hazel::Ref<Hazel::SubTexture2D> m_TextureTree;

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};
