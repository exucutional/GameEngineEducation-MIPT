#pragma once

#include "GameObject.h"

class CubeGameObject final : public GameObject
{
public:
	CubeGameObject();
	enum class BehavType
	{
		LeftRightControl,
		UpJump,
		FrontBackMove,
		None,
	};
	BehavType getType() const;
	void setType(BehavType type);
private:
	BehavType mtype;
};

