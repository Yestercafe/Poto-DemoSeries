#pragma once

#include "ptpch.h"

#include "Poto/Core.h"
#include "Poto/Events/Event.h"

namespace Poto
{
	/**
	 * @brief Windows 属性
	 */
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Poto Engine",
				unsigned int width = 1280,
				unsigned int height = 720)
					: Title(title), Width(width), Height(height)
		{
		}
	};
	
	// Interface representing a desktop system based Window
	class POTO_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		/**
		 * @brief 返回窗口宽度
		 */
		virtual unsigned int GetWidth() const = 0;
		/**
		 * @brief 返回窗口高度
		 */
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}
