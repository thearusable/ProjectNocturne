#ifndef NOC_WINDOW_WINDOW_HPP
#define NOC_WINDOW_WINDOW_HPP

#include <SDL.h>
#include <memory>
#include <string>

namespace noc::Window
{
class Window
{
public:
	Window(uint32_t width, uint32_t height, const std::string& title);

private:
	uint32_t    m_width;
	uint32_t    m_height;
	SDL_Window* m_pWindow;
	std::string m_title;
};

}   // namespace noc::Window

#endif   // NOC_WINDOW_WINDOW_HPP
