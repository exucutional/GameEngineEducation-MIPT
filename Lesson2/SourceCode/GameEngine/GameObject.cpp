#include "GameObject.h"

void GameObject::SetPosition(float x, float y, float z)
{
	m_vPosition[0] = x;
	m_vPosition[1] = y;
	m_vPosition[2] = z;

	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::MovePosition(float dx, float dy, float dz)
{
	m_vPosition[0] += dx;
	m_vPosition[1] += dy;
	m_vPosition[2] += dz;

	m_pRenderProxy->SetPosition(m_vPosition);
}
