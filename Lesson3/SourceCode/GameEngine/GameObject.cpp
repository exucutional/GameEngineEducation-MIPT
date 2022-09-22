#include "GameObject.h"

void GameObject::SetPosition(float x, float y, float z)
{
	m_vPosition[0] = x;
	m_vPosition[1] = y;
	m_vPosition[2] = z;

	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::SetVelocity(float x, float y, float z)
{
	m_vVelocity[0] = x;
	m_vVelocity[1] = y;
	m_vVelocity[2] = z;
}

Vector3d GameObject::GetPosition() const
{
	return { m_vPosition[0], m_vPosition[1], m_vPosition[2] };
}

Vector3d GameObject::GetVelocity() const
{
	return { m_vVelocity[0], m_vVelocity[1], m_vVelocity[2] };
}
