#include "BackGrass.h"

void BackGrass::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Back/backgrass.png");
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, 0, 30);
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(200, 70, 1);

	// 行列の合成は基本的にSRT
	m_mWorld = scaleMat * transMat;
}

void BackGrass::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
