#include "infpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

//#if INF_PLATFORM_WINDOWS
//#include "Platform/DirectX/DirectXBuffer.h"
//#endif
//#include "Platform/OpenGL/VulkanBuffer.h"

namespace Infinity
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
			case RendererAPI::None:   INF_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		}

		INF_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		case RendererAPI::None:   INF_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		}

		INF_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}