#pragma once

#include <memory>
#include <string>
#include <chrono>
#include <IInputListener.hpp>

namespace noc::game
{
class UserControllable : public noc::input::UserControllable
{
public:
	// @brief Callback function called each frame
	// @param deltaTime time passed since last frame (in ms)
	virtual void Tick(std::chrono::milliseconds deltaTime) { }

	/*
		IInputListener overrides
	*/
	/*void
	HandleInput(noc::input::NOC_KEY key, noc::input::NOC_KEY_STATE state) override
	{
	}
	
	void
	HandleAction(std::string_view actionName, noc::input::NOC_KEY_STATE state) override
	{
	}*/
};

}   // namespace noc::game

