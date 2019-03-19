#include "Input.hpp"
#include <SDL.h>
#include <functional>

namespace noc::input
{

template <class ListenerType>
static void
GenericRemoveListener(std::vector<ListenerType*>& vector, ListenerType* listener)
{
	const auto listenerIt = std::find(vector.begin(), vector.end(), listener);

	if(listenerIt != vector.end())
	{
		vector.erase(listenerIt);
	}
}

void


Input::RegisterMouseListener(IMouseListener* listener)
{
	m_mouseListeners.push_back(listener);
}

void
Input::RegisterKeyboardListener(IKeyboardListener* listener)
{
	m_keyboardListeners.push_back(listener);
}

void
Input::RemoveMouseListener(IMouseListener* listener)
{
	GenericRemoveListener(m_mouseListeners, listener);
}

void
Input::RemoveKeyboardListener(IKeyboardListener* listener)
{
	GenericRemoveListener(m_keyboardListeners, listener);
}

void
Input::HandleInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			// MOUSE EVENTS
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
				NotifyMouseListeners(event);
				break;

			// KEYBOARD EVENTS
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_KEYMAPCHANGED:
			case SDL_TEXTINPUT:
			case SDL_TEXTEDITING:
				NotifyKeyboardListeners(event);
				break;
				
			// OTHER EVENTS
			default:
				break;
		}
	}
}

void
Input::NotifyMouseListeners(const SDL_Event& event)
{
	switch(event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			for(auto listener : m_mouseListeners)
			{
				listener->HandleMouseButtonEvent(event.button);
			}
			break;

		case SDL_MOUSEMOTION:
			for(auto listener : m_mouseListeners)
			{
				listener->HandleMouseMotionEvent(event.motion);
			}
			break;

		case SDL_MOUSEWHEEL:
			for(auto listener : m_mouseListeners)
			{
				listener->HandleMouseWheelEvent(event.wheel);
			}
			break;

		default:
			break;
	}
}

void
Input::NotifyKeyboardListeners(const SDL_Event& event)
{
	for(auto listener : m_keyboardListeners) 
	{
		listener->HandleKeyboardEvent(static_cast<SDL_EventType>(event.type), event.key.keysym);
	}
}

}   // namespace noc::input
