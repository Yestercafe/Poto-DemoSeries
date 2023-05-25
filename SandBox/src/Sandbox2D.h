#pragma once

#include "Poto.h"

class Sandbox2D : public Poto::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Poto::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Poto::Event& e) override;
private:
	Poto::OrthographicCameraController m_CameraController;

	// Temp
	Poto::Ref<Poto::VertexArray> m_SquareVA;
	Poto::Ref<Poto::Shader> m_FlatColorShader;

	Poto::Ref<Poto::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};