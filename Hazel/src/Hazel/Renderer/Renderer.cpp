#include "hzpch.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Renderer/Renderer2D.h"

namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		// TODO setup camera, light and so on...
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit( const Ref<Shader>& shader, 
		const Ref<VertexArray>& vertexArray, 
		const glm::mat4 transfom)
	{
		// draw call

		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transfom);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
