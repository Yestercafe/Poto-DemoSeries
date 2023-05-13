#pragma once

#include "Poto/Core/Layer.h"

#include "Poto/Events/ApplicationEvent.h"
#include "Poto/Events/KeyEvent.h"
#include "Poto/Events/MouseEvent.h"

namespace Poto
{
	class POTO_API ImGuiLayer : public Layer
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
