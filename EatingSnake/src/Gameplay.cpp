#include "Gameplay.h"

#include "Random.h"
#include "imgui/imgui.h"

Gameplay::Gameplay()
    : Layer("Gameplay")
{
    auto& window = Poto::Application::Get().GetWindow();
    CreateCamera(window.GetWidth(), window.GetHeight());

    m_Level = Poto::CreateScope<Level>(std::make_pair(m_WorldWidth, m_WorldHeight));
    
    Random::Init();
}

void Gameplay::OnAttach()
{
    auto io = ImGui::GetIO();
    m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);
}

void Gameplay::OnDetach()
{
}

void Gameplay::OnUpdate(Poto::Timestep ts)
{
    m_WorldTimer += ts;

    if (m_GameState == GameState::Playing)
    {
        if (!m_Level->OnUpdate(ts))
        {
            m_GameState = GameState::Dead;
        }
    }
    
	Poto::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Poto::RenderCommand::Clear();

    Poto::Renderer2D::BeginScene(*m_Camera);
    m_Level->OnRender();
    Poto::Renderer2D::EndScene();
}

void Gameplay::OnImGuiRender()
{
}

void Gameplay::OnEvent(Poto::Event& event)
{
	Poto::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Poto::WindowResizeEvent>(PT_BIND_EVENT_FN(Gameplay::OnWindowResize));
    dispatcher.Dispatch<Poto::KeyPressedEvent>(PT_BIND_EVENT_FN(Gameplay::OnKeyPressed));
}

bool Gameplay::OnKeyPressed(Poto::KeyPressedEvent& e)
{
    switch (e.GetKeyCode())
    {
    case PT_KEY_UP:
    case PT_KEY_W:
        m_Level->SetSnakeDirection(Snake::Direction::Up);
        break;
    case PT_KEY_DOWN:
    case PT_KEY_S:
        m_Level->SetSnakeDirection(Snake::Direction::Down);
        break;
    case PT_KEY_LEFT:
    case PT_KEY_A:
        m_Level->SetSnakeDirection(Snake::Direction::Left);
        break;
    case PT_KEY_RIGHT:
    case PT_KEY_D:
        m_Level->SetSnakeDirection(Snake::Direction::Right);
        break;
    }
    return true;
}

bool Gameplay::OnMouseButtonPressed(Poto::MouseButtonPressedEvent& e)
{
    return false;
}

bool Gameplay::OnWindowResize(Poto::WindowResizeEvent& e)
{
    CreateCamera(e.GetWidth(), e.GetHeight());
    return false;
}

void Gameplay::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 12.f * m_WorldHeight / 21.f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = Poto::CreateScope<Poto::OrthographicCamera>(left, right, bottom, top);
}
