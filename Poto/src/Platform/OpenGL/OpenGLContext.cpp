#include "ptpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Poto
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		PT_CORE_ASSERT(windowHandle, "window handle is null")
	}
	void OpenGLContext::Init()
	{
		PT_PROFILE_FUNCTION()

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PT_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		PT_PROFILE_FUNCTION()

		glfwSwapBuffers(m_WindowHandle);
	}

}
