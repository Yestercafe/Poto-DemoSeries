#pragma once

#include "Poto/Input.h"

namespace Poto
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};
}
