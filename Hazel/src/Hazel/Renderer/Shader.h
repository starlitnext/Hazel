#pragma once

namespace Hazel {

	class Shader 
	{
	public:
		Shader(std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();

		void Bind();
		void UnBind();

	private:
		uint32_t m_RenderId;
	};

}
