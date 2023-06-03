#include "VideoPlayer.h"

#include "PngReader.h"

VideoPlayer::VideoPlayer(uint32_t fps, uint32_t amount)
    : Layer("VideoPlayer")
{
    m_FPS = fps;
	m_Amount = amount;

    auto& window = Poto::Application::Get().GetWindow();
    CreateCamera(window.GetWidth(), window.GetHeight());
}

void VideoPlayer::OnAttach()
{
}

void VideoPlayer::OnDetach()
{
}

void VideoPlayer::OnUpdate(Poto::Timestep ts)
{
	m_Timer += ts;
	
	Poto::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Poto::RenderCommand::Clear();

    Poto::Renderer2D::BeginScene(*m_Camera);
	Render();
    Poto::Renderer2D::EndScene();
}

void VideoPlayer::Render()
{
	if (m_INumber > m_Amount) return;
	
	PngReader reader(std::format("assets/bad_apple/{}.png", m_INumber += 1 + EXTRACTING_FRAME));
	const auto [pWidth, pHeight] = reader.GetSize();
	const auto& grayMat = reader.GetGrayMat();
	
	const glm::vec2 blockSize = {1.f, 1.f};
	const glm::vec2 originalPoint = {-pWidth / 2.f * blockSize.x + blockSize.x / 2.f,  -pHeight / 2.f * blockSize.y + blockSize.y / 2.f};

	auto getGrayedWhite = [](float factor) -> glm::vec4
	{
		return {factor, factor, factor, 1.f};
	};
	
	for (int x = 0; x < pWidth; ++x)
	{
		for (int y = 0; y < pHeight; ++y)
		{
			const glm::vec2 pos = {originalPoint.x + x * blockSize.x, originalPoint.y + y * blockSize.y};
			Poto::Renderer2D::DrawQuad(pos, blockSize, getGrayedWhite(grayMat[x][y]));
		}
	}
}

void VideoPlayer::OnImGuiRender()
{
}

void VideoPlayer::OnEvent(Poto::Event& event)
{
	Poto::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Poto::WindowResizeEvent>(PT_BIND_EVENT_FN(VideoPlayer::OnWindowResize));
}

bool VideoPlayer::OnWindowResize(Poto::WindowResizeEvent& e)
{
    CreateCamera(e.GetWidth(), e.GetHeight());
    return false;
}

void VideoPlayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = -(float)width / (float)height;
	float camWidth = 25.f / 2.f;
	float bottom = camWidth;
	float top = -camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = Poto::CreateScope<Poto::OrthographicCamera>(left, right, bottom, top);
}

