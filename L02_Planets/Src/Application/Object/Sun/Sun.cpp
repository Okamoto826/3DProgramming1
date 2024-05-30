#include "Sun.h"

void Sun::Init()
{
	m_model.Load("Asset/Data/LessonData/Planets/sun.gltf");
	m_rotNum = 0;
}

void Sun::Update()
{
	m_rotNum += 0.1;
	m_rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotNum));
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_rotMat);
}
