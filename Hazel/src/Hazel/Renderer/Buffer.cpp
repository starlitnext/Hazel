#include "hzpch.h"

#include "Buffer.h"
#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); nullptr;
		case RenderAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None: HZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); nullptr;
		case RenderAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
		return nullptr;
	}

}

