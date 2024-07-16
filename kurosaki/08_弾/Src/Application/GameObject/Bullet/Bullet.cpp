#include "Bullet.h"
#include"../../Scene/SceneManager.h"

void Bullet::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Bullet/Bullet.gltf");

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

}

void Bullet::Update()
{
	m_pos += m_dir * m_speed;

	m_lifeSpan--;
	if (m_lifeSpan < 0)m_isExpired = true;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Bullet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Bullet::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Bullet::PostUpdate()
{
	// 当たり判定(スフィア)
	KdCollider::SphereInfo atkSphere;
	atkSphere.m_sphere.Center = m_pos;
	atkSphere.m_sphere.Center.y += 0.1;
	atkSphere.m_sphere.Radius = 1.0f;
	atkSphere.m_type = KdCollider::TypeDamage;

	m_pDebugWire->AddDebugSphere(atkSphere.m_sphere.Center, atkSphere.m_sphere.Radius);

	// 全オブジェクトとの当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(atkSphere, nullptr))
		{
			// 当たった
			obj->OnHit();
		}
	}
}

void Bullet::SetParam(Math::Vector3 _pos, Math::Vector3 _dir, float _speed, int _lifeSpan)
{
	m_pos = _pos;
	m_dir = _dir;
	m_speed = _speed;
	m_lifeSpan = _lifeSpan;
}

void Bullet::OnHit()
{
	m_isExpired = false;
}
