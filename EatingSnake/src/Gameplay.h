#pragma once
#include <Poto.h>

#include "Level.h"
#include "imgui/imgui.h"

class Gameplay : public Poto::Layer
{
public:
    Gameplay();
    virtual ~Gameplay() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Poto::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Poto::Event& event) override;
	bool OnMouseButtonPressed(Poto::MouseButtonPressedEvent& e);
	bool OnKeyPressed(Poto::KeyPressedEvent& e);
	bool OnWindowResize(Poto::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
	
	Poto::Scope<Poto::OrthographicCamera> m_Camera;
	
	enum class GameState
	{
		Menu = 0,
		Playing = 1,
		Dead = 2,
	} m_GameState = GameState::Menu;

	ImFont* m_Font;
	float m_WorldTimer{};
	Poto::Scope<Level> m_Level;

	uint m_WorldWidth = 51u, m_WorldHeight = 37u;
};
