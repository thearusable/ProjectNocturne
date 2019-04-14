#pragma once

#include <IKeyboardListener.hpp>
#include <IMouseListener.hpp>
#include <memory>
#include <string>
#include <vector>

namespace noc::window
{
class Window
{
public:
	Window(uint32_t width, uint32_t height, const std::string& title);
	~Window();

	void
	RegisterMouseListener(IMouseListener* listener);

	void
	RegisterKeyboardListener(IKeyboardListener* listener);

	void
	RemoveMouseListener(IMouseListener* listener);

	void
	RemoveKeyboardListener(IKeyboardListener* listener);

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

	std::vector<IKeyboardListener*> m_keyboardListeners;
	std::vector<IMouseListener*>    m_mouseListeners;

	void
	NotifyMouseListeners(const SDL_Event& event);

	void
	NotifyKeyboardListeners(const SDL_Event& event);
};

}   // namespace noc::window
