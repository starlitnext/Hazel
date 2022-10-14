#include "hzpch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		return nullptr;
	}

}
