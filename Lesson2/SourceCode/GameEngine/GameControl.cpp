#include "GameControl.h"
#include "../../../SDKs/inih/include/INIReader.h"

GameControl::GameControl() :
	moveSpeed(0),
	configWinMap {
		{ "larrow", VK_LEFT },
		{ "rarrow", VK_RIGHT },
		{ "uarrow", VK_UP },
		{ "darrow", VK_DOWN },
		{ "space",  VK_SPACE },
		{ "shift",  VK_SHIFT },
	},
	controlMap()
{
	if (ReadConfig("../../../Assets/Configs/actionmap.ini"))
		assert(0);
}

int GameControl::ReadConfig(const std::string& config)
{
	INIReader reader(config);

	if (reader.ParseError() < 0)
		return -1;

	moveSpeed = reader.GetReal("Speed", "Movement", 0.0);

	std::vector<std::pair<ControlAction, std::string>> controlStringMap
	{
		{ ControlAction::GoLeft, "GoLeft" },
		{ ControlAction::GoRight, "GoRight" },
		{ ControlAction::GoUp, "GoUp" },
		{ ControlAction::GoDown, "GoDown" },
		{ ControlAction::GoForward, "GoForward" },
		{ ControlAction::GoBackward, "GoBackward" },
	};

	for (auto& controlPair : controlStringMap)
	{
		auto key = configWinMap.find(reader.Get("Keyboard", controlPair.second, ""));
		if (key != std::end(configWinMap))
			controlMap.insert({ key->second, controlPair.first });
		else
			return -2;
	}

	return 0;
}

ControlAction GameControl::Control() const
{
	for (const auto& [key, action] : controlMap)
	{
		if (GetKeyState(key) & 0x8000)
			return action;
	}
	return ControlAction::None;
}

void GameControl::ControlObject(ControlAction action, GameObject& gobject) const
{
	switch (action) {
	case ControlAction::GoLeft:
		gobject.MovePosition(-moveSpeed, 0, 0);
		break;
	case ControlAction::GoRight:
		gobject.MovePosition(moveSpeed, 0, 0);
		break;
	case ControlAction::GoDown:
		gobject.MovePosition(0, -moveSpeed, 0);
		break;
	case ControlAction::GoUp:
		gobject.MovePosition(0, moveSpeed, 0);
		break;
	case ControlAction::GoForward:
		gobject.MovePosition(0, 0, moveSpeed);
		break;
	case ControlAction::GoBackward:
		gobject.MovePosition(0, 0, -moveSpeed);
		break;
	case ControlAction::None:
		break;
	default:
		assert(0);
	}
}
