#include "hzpch.h"

#include "Hazel/Renderer/Renderer.h"

namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		// TODO setup camera, light and so on...
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit( const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray, 
		const glm::mat4 transfom)
	{
		// draw call

		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transfom);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
