#pragma once
#include <SDL_events.h>

namespace noc::input
{

class IKeyboardListener
{
public:
	virtual void HandleKeyboardEvent(SDL_EventType type, SDL_Keysym ) = 0;
};

}   // namespace noc::input

