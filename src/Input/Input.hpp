#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include "KeyCodes.hpp"
#include <glm.hpp>

namespace noc::input
{
class UserControllable;

class Input
{
	using actionKeyPair = std::pair<std::string, NOC_KEY>;

	std::unordered_map<std::string, NOC_KEY> m_actionKeyMap;
	std::vector<std::optional<actionKeyPair>> m_actionKeyState;

// TODO: CHANGE TO VEC2
	uint32_t m_mouseX;
	uint32_t m_mouseY;

	glm::vec2 m_mousePos;

public:
	// @brief Used by UserControllable object to register for certain action
	// @param sactionName string represented action
	// @param state state of the action in which user is interested
	void
	RegisterForActionEvent(UserControllable* object, std::string_view actionName, NOC_KEY_STATE state);

	bool
	CheckKeyPressed(NOC_KEY keyKode);

	bool
	CheckAction(std::string_view action);

	void
	SetUpKeyMap(std::string_view configFile);

	void
	HandleInput();
private:

	void
	SetActionKeyPressed(NOC_KEY keyCode);

	void
	SetActionKeyReleased(NOC_KEY keyCode);

// TODO CHANGE TO VEC2
	void
	SetMousePosition(uint32_t x, uint32_t y);
};

}   // namespace noc::input

