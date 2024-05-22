#include "Player.h"

void Player::Init()
{
	m_polygon.SetMaterial("Asset/Textures/char.png");

	m_polygon.SetSplit(6, 6);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon);
}

void Player::Update()
{
	m_polygon.SetUVRect(8);
}
