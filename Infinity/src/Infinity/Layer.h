#pragma once

#include "Infinity/Core.h"
#include "Infinity/Events/Event.h"

namespace Infinity
{
	// This is an abstract class for creating application layers.
	// Sub-class this class for custom application layers.
	class INFINITY_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		// When the layer is pushed onto the layer stack, and becomes apart of our application (On Init).
		virtual void OnAttach() {}

		// When it gets removed from the layer stack (On Shutdown).
		virtual void OnDetach() {}

		// Gets called by the application when the layer is updated. (Every Frame)
		virtual void OnUpdate() {}

		// Whenever an event gets send to the layer.
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected: 
		const std::string m_DebugName;
	};
}