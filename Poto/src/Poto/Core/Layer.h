#pragma once

#include "Poto/Core/Core.h"
#include "Poto/Core/Timestep.h"
#include "Poto/Events/Event.h"

namespace Poto
{
	class POTO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		/**
		 * @brief when a event sent to layer
		 */
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_Debugname; }

	protected:
		std::string m_Debugname;
	};
}