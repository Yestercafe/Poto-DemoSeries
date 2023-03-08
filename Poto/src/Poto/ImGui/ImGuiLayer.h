#pragma once

#include "Poto/Layer.h"

namespace Poto
{
	class POTO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEnvent(Event& event) override;

	private:
		float m_Time = 0.0f;
	};
}
