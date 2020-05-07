#include "infpch.h"
#include "LayerStack.h"

namespace Infinity
{
	LayerStack::LayerStack() 
	{ 
		// When we construct a stack, we want the iterator to be at the beginning of the vector.
		m_LayerInsert = m_Layers.begin();
	}
	LayerStack::~LayerStack() 
	{ 
		/* TODO: Layers in the stack will only currently be deleted if they remain in the stack for the lifecycle of the application.
		* So if you pop a layer, its no longer associated with the stack, and will not be deleted.
		* Potentially revise this in the future as different stacks might be present across different levels etc. */
		for (Layer* layer : m_Layers)
			delete layer;
	}

	// Will push the layer as the last layer, but never infront of an overlay.
	void LayerStack::PushLayer(Layer * layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
		layer->OnAttach();
	}

	// Will push an overlay to the end always.
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	// Pops a layer off the layer stack
	void LayerStack::PopLayer(Layer * layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	// Pops an overlay layer off the layer stack
	void LayerStack::PopOverlay(Layer * overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}
}
