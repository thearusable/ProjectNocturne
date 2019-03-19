#pragma once

#include <memory>
#include <string>
#include <vector>
#include <IMouseListener.hpp>
#include <IKeyboardListener.hpp>

namespace noc::input
{
class Input
{
public:
	void
	RegisterMouseListener(IMouseListener* listener);

	void
	RegisterKeyboardListener(IKeyboardListener* listener);

	void
	RemoveMouseListener(IMouseListener* listener);

	void
	RemoveKeyboardListener(IKeyboardListener* listener);
	
	void
	HandleInput();
	
private:
	std::vector<IKeyboardListener*> m_keyboardListeners;
	std::vector<IMouseListener*> m_mouseListeners;

	void
	NotifyMouseListeners(const SDL_Event& event);

	void
	NotifyKeyboardListeners(const SDL_Event& event);
};

}   // namespace noc::input

