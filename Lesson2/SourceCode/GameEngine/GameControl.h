#pragma once

#include <string>
#include <unordered_map>
#include "GameObject.h"

enum class ControlAction
{
	GoLeft,
	GoRight,
	GoDown,
	GoUp,
	GoForward,
	GoBackward,
	None,
};

class GameControl
{
public:
	GameControl();
	int ReadConfig(const std::string& config);
	ControlAction Control() const;
	void ControlObject(ControlAction action, GameObject& gobject) const;
private:
	float moveSpeed;
	std::unordered_map<std::string, UINT> configWinMap;
	std::unordered_map<UINT, ControlAction> controlMap;
};
