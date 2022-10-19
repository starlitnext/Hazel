#include "hzpch.h"

#include "GraphicsContext.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Hazel {

	Ref<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
