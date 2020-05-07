#pragma once

#include "Infinity/Core.h"
#include "Layer.h"

#include <vector>

namespace Infinity
{
	/// <summary>
	/// This class simply acts as a wrapper for the <see cref="m_Layers"/> vector.
	/// <para>This stack will be iterated over (forward and backwards depending on situation) every frame.</para>
	/// <para>This class will take ownership over any <see cref="Layer"/> passed into it. Layers are owned by this stack.</para>
	/// </summary>
	class INFINITY_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end()   { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;

		// Tracks the position of layer inserting, which is only at the end of layers and not overlays.
		// So adding an overlay won't affect this iterator, so therefore the next time you add a layer,
		// regardless of how many overlays you've added, it will never be infront of any overlays.
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}