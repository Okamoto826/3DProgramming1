#include "Moon.h"
#include"../Earth/Earth.h"

void Moon::Init()
{
	m_model.Load("Asset/Data/LessonData/Planets/moon.gltf");
	m_rotNum = 0;
	m_revoNum = 0;
	m_revoMoonNum = 0;
}

void Moon::Update()
{
	Earth earth;
	Math::Matrix earthMat = earth.GetMat();

	m_rotNum += 1;
	m_revoNum += 0.25;
	m_revoMoonNum += 3;



	m_rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotNum));
	m_revoMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_revoNum));
	/*m_transMat = Math::Matrix::CreateTranslation
	(5*cos(DirectX::XMConvertToRadians(m_revoNum))+ 2 * cos(DirectX::XMConvertToRadians(m_revoMoonNum)),0,
		-5 * sin(DirectX::XMConvertToRadians(m_revoNum)) - 2 * sin(DirectX::XMConvertToRadians(m_revoMoonNum)));*/

	m_transMat = Math::Matrix::CreateTranslation
	( 2 * cos(DirectX::XMConvertToRadians(m_revoMoonNum)), 0,
	 - 2 * sin(DirectX::XMConvertToRadians(m_revoMoonNum)));
	m_world = m_rotMat * m_transMat * earthMat;
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_world);
}
