#include "Input.hpp"
#include <SDL_events.h>
#include <functional>
#include <iostream>

namespace noc::input
{

void
Input::HandleInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.key.keysym.scancode != SDL_GetScancodeFromKey(event.key.keysym.sym))
		{
			//printf("Physical %s acting as %s key\n", SDL_GetScancodeName(event.key.keysym.scancode), SDL_GetKeyName(event.key.keysym.sym));
			std::cout << SDL_GetScancodeName(event.key.keysym.scancode) << SDL_GetKeyName(event.key.keysym.sym) << '\n';
		}
    		

		// switch(event.type)
		// {
		// 	case SDL_MOUSEMOTION:
		// 		SetMousePosition(event.motion.x, event.motion.y);
		// 		break;

		// 	case SDL_MOUSEBUTTONDOWN:
		// 		SetActionKeyPressed();
		// 		break;
		// 	case SDL_KEYDOWN:
		// 		SetActionKeyPressed();
		// 		break;

		// 	case SDL_MOUSEBUTTONUP:
		// 	case SDL_KEYUP:
		// 		SetActionKeyReleased();
		// 		break;

		// 	case SDL_MOUSEWHEEL:
		// 		break;

		// 	// OTHER EVENTS
		// 	default:
		// 		break;
		// }
	}
}

}   // namespace noc::input
