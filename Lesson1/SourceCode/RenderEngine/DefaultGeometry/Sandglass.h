#pragma once

#include "../RenderObject.h"

class Sandglass : public RenderObject
{
public:
	Sandglass();

private:
	inline static const PosColorVertex s_sandglassVertices[] =
	{
		{ -0.5f, 0.0f,  0.5f, 0xff000000 },
		{ 0.5f,  0.0f,  0.5f, 0xff0000ff },
		{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
		{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
		{-0.5f,  0.0f, -0.5f, 0xffff0000 },
		{ 0.5f,  0.0f, -0.5f, 0xffff00ff },
		{-1.0f, -1.0f, -1.0f, 0xffffff00 },
		{ 1.0f, -1.0f, -1.0f, 0xffffffff },
		{-1.0f,  1.0f,  1.0f, 0xff000000 },
		{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
		{-1.0f,  1.0f, -1.0f, 0xff00ff00 },
		{ 1.0f,  1.0f, -1.0f, 0xff00ffff },
	};

	inline static const uint16_t s_sandglassTriList[] =
	{
		0, 1, 2,   // 0
		1, 3, 2,
		4, 6, 5,   // 2
		5, 6, 7,
		0, 2, 4,   // 4
		4, 2, 6,
		1, 5, 3,   // 6
		5, 7, 3,
		//0, 4, 1,   // 8
		//4, 5, 1,
		2, 3, 6,   // 10
		6, 3, 7,
		8, 1, 0,   // 12
		8, 9, 1,
		9, 5, 1,   // 14
		9, 11, 5,
		11, 10, 4, // 16
		11, 4, 5,
		10, 8, 0, // 18
		10, 0, 4,
		10, 11, 9,
		10, 9, 8,
	};
};

