#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

namespace Hazel {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		// render forwards
		// dispatch backforwards
		std::vector<Layer*> m_Layers;
		// before m_LayerInsert is common layers, after m_LayerInsert is overlays
		std::vector<Layer*>::iterator m_LayerInsert;
	};

}
