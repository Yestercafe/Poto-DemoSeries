#include "ptpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Poto
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* S_Data;

	void Renderer2D::Init()
	{
		S_Data = new Renderer2DStorage();
		S_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord"}
			});
		S_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3 ,0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		S_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		S_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		S_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		S_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		S_Data->TextureShader->Bind();
		S_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
		delete S_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		S_Data->TextureShader->Bind();
		S_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
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
		S_Data->TextureShader->SetFloat4("u_Color", color);
		S_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		S_Data->TextureShader->SetMat4("u_Transform", transform);
		S_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(S_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ Position.x, Position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		S_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		S_Data->TextureShader->SetMat4("u_Transform", transform);

		S_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(S_Data->QuadVertexArray);
	}

}
