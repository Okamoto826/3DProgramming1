#include "ship.h"

void Ship::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/ship.gltf");


	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, -2, 0);
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(0.3);
	

	// 行列の合成は基本的にSRT
	m_mWorld = scaleMat * transMat;

	// 当たり判定用の初期化
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("ShipCollision", m_model, KdCollider::TypeGround);
}

void Ship::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
