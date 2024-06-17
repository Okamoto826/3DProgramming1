#include "Back.h"

void Back::Init()
{
	m_polygon.SetMaterial("Asset/Textures/back.png");
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, 0, 50);
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(300, 100, 1);

	// 行列の合成は基本的にSRT
	m_mWorld = scaleMat * transMat;
}

void Back::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
