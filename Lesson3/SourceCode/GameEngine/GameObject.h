#pragma once

#include "Common.h"
#include "RenderProxy.h"

struct Vector3d
{
	float x;
	float y;
	float z;
};

class GameObject
{
public:
	GameObject() = default;

	~GameObject()
	{
		delete m_pRenderProxy;
	}

	void SetPosition(float x, float y, float z);
	void SetVelocity(float x, float y, float z);

	RenderProxy* const GetRenderProxy() { return m_pRenderProxy; }
	Vector3d GetPosition() const;
	Vector3d GetVelocity() const;
protected:
	RenderProxy* m_pRenderProxy;

	float m_vPosition[3];
	float m_vVelocity[3];
};

