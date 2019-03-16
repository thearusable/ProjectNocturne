#ifndef NOC_WINDOW_WINDOW_HPP
#define NOC_WINDOW_WINDOW_HPP

#include <memory>
#include <string>

class SDL_Window;

namespace noc::window
{
class Window
{
public:
	Window(uint32_t width, uint32_t height, const std::string& title);
	~Window();

	void
	Resize(uint32_t newWidth, uint32_t newHeight);

	void
	SetIcon(const std::string& file);
	
	void
	HandleInput();

	void
	Clear(float r, float g, float b, float a);

	void
	SwapBuffers();

	void
	WrapMouse(bool choice);
	
	void
	ShowCursor(bool choice);
	
private:
	uint32_t    m_width;
	uint32_t    m_height;
	SDL_Window* m_pWindow;
	std::string m_title;
};

}   // namespace noc::window

#endif   // NOC_WINDOW_WINDOW_HPP
