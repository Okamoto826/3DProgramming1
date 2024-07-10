#include "Moto.h"
#include"../Tank/Tank.h"

void Moto::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/moto/moto.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Moto", m_model, KdCollider::TypeDamage);
}

void Moto::Update()
{
	Math::Vector3 m_move = {};
	m_speed = 0.06;
	if (m_target.expired() == false)
	{
		
		Math::Vector3 targetPos = m_target.lock()->GetPos();
		m_move = targetPos - m_pos;
		if (m_move.Length() < m_speed)m_speed = m_move.Length();
	}
	m_move.Normalize();
	m_pos += m_move * m_speed;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Moto::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
