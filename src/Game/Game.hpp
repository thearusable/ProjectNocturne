#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include <KeyCodes.hpp>
#include "IUserControllable.hpp"

namespace noc::game
{

class Game
{
public:
	void AddGameObject(UserControllable*);

private:

	std::vector<std::unique_ptr<UserControllable>> m_userObjects;
};

}   // namespace noc::game

