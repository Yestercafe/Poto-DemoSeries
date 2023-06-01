#pragma once

#include "Poto.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Poto::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Poto::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Poto::Event& event) override;
	bool OnMouseButtonPressed(Poto::MouseButtonPressedEvent& e);
	bool OnWindowResize(Poto::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Poto::Scope<Poto::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_GameState = GameState::MainMenu;
};
