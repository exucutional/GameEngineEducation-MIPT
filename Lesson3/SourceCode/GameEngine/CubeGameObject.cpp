#include "CubeGameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

CubeGameObject::CubeGameObject():
	mtype(CubeGameObject::BehavType::None)
{
	m_pRenderProxy = new CubeRenderProxy();
}

void CubeGameObject::setType(CubeGameObject::BehavType type)
{
	mtype = type;
}

CubeGameObject::BehavType CubeGameObject::getType() const
{
	return mtype;
}