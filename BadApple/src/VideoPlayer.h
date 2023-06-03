#pragma once

#include <Poto.h>

class VideoPlayer : public Poto::Layer
{
public:
    VideoPlayer(uint32_t fps, uint32_t amount);
    virtual ~VideoPlayer() = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    void OnUpdate(Poto::Timestep ts) override;
    virtual void OnImGuiRender() override;
    
    void OnEvent(Poto::Event& event) override;
	bool OnWindowResize(Poto::WindowResizeEvent& e);
private:
    void CreateCamera(uint32_t width, uint32_t height);
    Poto::Scope<Poto::OrthographicCamera> m_Camera;
    void Render();
private:
    uint32_t m_FPS;
    float m_Timer = 0.f;
    uint32_t m_Amount;
    uint32_t m_INumber = 1;
    uint32_t EXTRACTING_FRAME = 2;
};
