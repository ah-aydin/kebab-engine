#pragma once

#ifdef GRAPHICS_API_OPENGL

#include <Engine/Application.h>
#include "Rendering/GLRenderer.h"

#include "GLWindow.h"

namespace kbb::glApi
{
	class GLApplication : public Application
	{
	public:
		GLApplication();
		~GLApplication();

		void run() override;

	private:
		GLWindow m_window{ "OpenGl Application" };
		GLRenderer m_renderer{ };
	};
}
#endif