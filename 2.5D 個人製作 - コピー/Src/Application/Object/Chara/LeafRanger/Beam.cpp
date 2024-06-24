#include "Beam.h"

void Beam::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Weapon/leafrangerweapon.png");
}

void Beam::Update()
{
}

void Beam::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
