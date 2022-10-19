#pragma once

#include <Hazel.h>
#include <imgui.h>

#include "Level.h"


class GameLayer : public Hazel::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Hazel::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Hazel::Event& event) override;

	bool OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e);;
	bool OnWindowResize(Hazel::WindowResizeEvent& e);;
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Hazel::Scope<Hazel::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	float m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};
	GameState m_State = GameState::MainMenu;
};
