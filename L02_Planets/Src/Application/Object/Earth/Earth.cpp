#include "Earth.h"

void Earth::Init()
{
	
	m_model.Load("Asset/Data/LessonData/Planets/earth.gltf");
	m_rotNum = 0;
	m_revoNum = 0;
	
}

void Earth::Update()
{
	m_rotNum += 91.25;
	m_revoNum += 0.25;

	m_rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotNum));
	m_transMat = Math::Matrix::CreateTranslation(5*cos(DirectX::XMConvertToRadians(m_revoNum)),0, -5 * sin(DirectX::XMConvertToRadians(m_revoNum)));
	m_world = m_rotMat * m_transMat;
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_world);
}
