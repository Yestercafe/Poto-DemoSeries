#include "Gameplay.h"

#include "Random.h"
#include "imgui/imgui.h"
#include <format>

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
    auto& window = Poto::Application::Get().GetWindow();
    auto pos = ImGui::GetWindowPos();
    auto width = window.GetWidth();
    auto height = window.GetHeight();
    
    int color = 0xff0000ff;
    auto factor = static_cast<uint>(m_WorldTimer * 50);
    auto epoch = factor / 0xff;
    auto r = factor % 0xff;
    auto g = 0xfe - factor % 0xff;
    if (epoch & 1)
    {
        std::swap(r, g);
    }
    color |= (r << 16);
    color |= (g <<  8);
    
    switch (m_GameState)
    {
    case GameState::Playing:
        {
            const auto score = m_Level->GetScore();
            const auto scoreStr = std::format("Score: {}", score);
            ImGui::GetOverlayDrawList()->AddText(m_Font, 48.f, pos, color, scoreStr.c_str());
            break;
        }
    case GameState::Menu:
        {
            const std::string content {"Press any key to play"};
            auto textBoxSize = m_Font->CalcTextSizeA(72.f, 0.f, 0.f, content.c_str());
            pos.x += width * 0.25f;
            pos.y += height * 0.2f;
            ImGui::GetOverlayDrawList()->AddText(m_Font, 72.f, pos, color, content.c_str());
            break;
        }
    case GameState::Dead:
        {
            const auto score = m_Level->GetScore();
            const auto str1 = std::format("Game over!");
            const auto str2 = std::format("Your final score is: {}", score);
            const auto str3 = std::format("Press any key to retry");
            pos.x += width * 0.2f;
            pos.y += height * 0.15f;
            ImGui::GetOverlayDrawList()->AddText(m_Font, 48.f, pos, color, str1.c_str());
            pos.y += 40.f;
            ImGui::GetOverlayDrawList()->AddText(m_Font, 48.f, pos, color, str2.c_str());
            pos.y += 40.f;
            ImGui::GetOverlayDrawList()->AddText(m_Font, 48.f, pos, color, str3.c_str());
            break;
        }
    }
}

void Gameplay::OnEvent(Poto::Event& event)
{
	Poto::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Poto::WindowResizeEvent>(PT_BIND_EVENT_FN(Gameplay::OnWindowResize));
    dispatcher.Dispatch<Poto::KeyPressedEvent>(PT_BIND_EVENT_FN(Gameplay::OnKeyPressed));
}

bool Gameplay::OnKeyPressed(Poto::KeyPressedEvent& e)
{
    switch (m_GameState)
    {
    case GameState::Menu:
        m_GameState = GameState::Playing;
        return true;
    case GameState::Dead:
        m_Level->Reset();
        m_GameState = GameState::Playing;
        return true;
    }
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
