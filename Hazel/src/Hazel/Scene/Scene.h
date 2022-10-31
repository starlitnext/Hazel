#pragma once

#include <entt.hpp>
#include "Hazel/Core/Timestep.h"

namespace Hazel {

	class Scene
	{
	public:
		Scene();
		~Scene();

		// TEMP
		entt::registry& Reg() { return m_Registry; };

		entt::entity CreateEntity();

		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_Registry;
	};

}
