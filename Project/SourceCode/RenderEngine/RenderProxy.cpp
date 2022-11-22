#include "RenderProxy.h"

void RenderProxy::SetPosition(float position[3])
{
	m_vPosition[0] = position[0];
	m_vPosition[1] = position[1];
	m_vPosition[2] = position[2];
}

float RenderProxy::GetScale() const
{
	return m_scale;
}

bool RenderProxy::IsRenderable() const
{
	return m_isRenderable;
}

void RenderProxy::SetScale(float value)
{
	m_scale = value;
}

void RenderProxy::SetRenderable(bool value)
{
	m_isRenderable = value;
}
