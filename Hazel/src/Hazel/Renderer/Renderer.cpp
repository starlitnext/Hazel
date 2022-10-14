#include "hzpch.h"

#include "Hazel/Renderer/Renderer.h"

namespace Hazel {


	void Renderer::BeginScene()
	{
		// TODO setup camera, light and so on...
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		// draw call
		// TODO submit to other thread
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
