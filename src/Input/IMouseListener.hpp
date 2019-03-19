#pragma once
#include <SDL_events.h>

namespace noc::input
{

class IMouseListener
{
public:
	virtual void
	HandleMouseButtonEvent(const SDL_MouseButtonEvent& event) = 0;

	virtual void
	HandleMouseMotionEvent(const SDL_MouseMotionEvent& event) = 0;

	virtual void
	HandleMouseWheelEvent(const SDL_MouseWheelEvent& event) = 0;
};

}   // namespace noc::input

