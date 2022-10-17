#include "hzpch.h"

#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel {

	Hazel::Ref<Hazel::Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
