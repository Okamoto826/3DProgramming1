#include "Player.h"

void Player::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Player/Player.gltf");
	m_pos = {0,2.2,0};
}

void Player::Update()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	// 回転行列
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	m_mWorld = rotMat * transMat;
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
