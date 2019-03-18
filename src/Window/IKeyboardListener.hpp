#pragma once
#include <SDL_events.h>

namespace noc::window
{

class IKeyboardListener
{
public:
	virtual void HandleKeyboardEvent(SDL_EventType type, SDL_Keysym ) = 0;
};

}   // namespace noc::window

