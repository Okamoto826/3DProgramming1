#include "BackTree.h"

void BackTree::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Back/backtree.png");
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, 1.3, 10);
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(120, 20, 1);

	// 行列の合成は基本的にSRT
	m_mWorld = scaleMat * transMat;
}

void BackTree::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
