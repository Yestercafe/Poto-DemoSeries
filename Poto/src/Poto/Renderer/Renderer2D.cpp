#include "ptpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Poto
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* S_Data;

	void Renderer2D::Init()
	{
		S_Data = new Renderer2DStorage();
		S_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		// squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
			});
		S_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3 ,0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		// squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		S_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		S_Data->FlatColorShader = Shader::Create("assets / shaders / FlatColor.glsl");
	}

	void Renderer2D::ShutDown()
	{
		delete S_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(S_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(S_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(S_Data->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
		
	}

	void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ Position.x, Position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(S_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Poto::OpenGLShader>(S_Data->FlatColorShader)->UploadUniformFloat4("u_Color", color);

		S_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(S_Data->QuadVertexArray);
	}


}
