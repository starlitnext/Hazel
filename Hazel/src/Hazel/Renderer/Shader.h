#pragma once

#include <glm/glm.hpp>

namespace Hazel {

	class Shader 
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(std::string& vertexSrc, std::string& fragmentSrc);
	};

}
