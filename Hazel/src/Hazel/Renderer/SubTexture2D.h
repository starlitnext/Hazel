#pragma once

#include "Hazel/Renderer/Texture.h"

#include <glm/glm.hpp>

namespace Hazel {

	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& maxe);

		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = glm::vec2(1.0f));
	private:
		Ref<Texture2D> m_Texture;

		glm::vec2 m_TexCoords[4];
	};

}
