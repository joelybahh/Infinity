#pragma once

#include "Infinity/Layer.h"
#include "Infinity/Events/ApplicationEvent.h"
#include "Infinity/Events/MouseEvent.h"
#include "Infinity/Events/KeyEvent.h"

namespace Infinity
{
	class INFINITY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
