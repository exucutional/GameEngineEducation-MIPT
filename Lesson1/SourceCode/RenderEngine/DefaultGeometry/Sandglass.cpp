#include "Sandglass.h"
#include "../Shaders/ShadersHelper.h"

Sandglass::Sandglass()
{
	m_Layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_sandglassVertices, sizeof(s_sandglassVertices))
		, m_Layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_sandglassTriList, sizeof(s_sandglassTriList))
	);

	m_ProgramHandle = ShadersHelper::LoadProgram("vs_cubes", "fs_cubes");
}