#include "kbbpch.h"
#include "OpenGLContext.h"

#include "OpenGLCore.h"

#include <GLFW/glfw3.h>

namespace kbb::renderer
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{}

	void OpenGLContext::init()
	{
		KBB_CORE_INFO("Initializing OpenGL context");
		KBB_CORE_INFO("\tInitializing GLAD");
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
		{
			KBB_CORE_ERROR("GLAD initialization failed");
		}
		KBB_CORE_INFO("\tOpenGL vendor: {0}", (const char*) glGetString(GL_VENDOR));
		KBB_CORE_INFO("\tOpenGL renderer: {0}", (const char*) glGetString(GL_RENDERER));
		KBB_CORE_INFO("\tOpenGL version: {0}", (const char*) glGetString(GL_VERSION));

		KBB_GL_CALL(glEnable(GL_DEPTH_TEST));
		KBB_GL_CALL(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS));
	}

	void OpenGLContext::swapBuffers() const
	{
		glfwSwapBuffers(m_windowHandle);
	}

	void OpenGLContext::terminate()
	{

	}
}