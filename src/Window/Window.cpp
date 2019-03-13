#include "Window.hpp"
#include <GL/glew.h>

namespace noc::Window
{
Window::Window(uint32_t width, uint32_t height, const std::string& title)
   : m_width(width)
   , m_height(height)
   , m_title(title)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_pWindow = SDL_CreateWindow(m_title.c_str(),
	   SDL_WINDOWPOS_UNDEFINED,   // initial x position
	   SDL_WINDOWPOS_UNDEFINED,   // initial y position
	   m_width,                   // width, in pixels
	   m_height,                  // height, in pixels
	   SDL_WINDOW_OPENGL          // flags - see below
	);

	SDL_GLContext glContext = SDL_GL_CreateContext(m_pWindow);

	GLenum status = glewInit();
}

}   // namespace noc::Window
