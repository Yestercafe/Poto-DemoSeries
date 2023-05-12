#include "ptpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Poto {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}