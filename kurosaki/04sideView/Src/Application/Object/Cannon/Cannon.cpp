#include "Cannon.h"

void Cannon::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/Cannon.gltf");


	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, -2, 0);
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(1.0);
	Math::Matrix rotMat;
	rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));

	// 行列の合成は基本的にSRT
	m_mWorld = scaleMat * rotMat * transMat;

	// 当たり判定用の初期化
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("CannonCollision", m_model, KdCollider::TypeGround);
}
void Cannon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
