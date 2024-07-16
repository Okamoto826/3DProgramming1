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
	UpdateRotate(m_move);
	// キャラクターのワールド行列を創る処理
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotMat * transMat;
}

void Moto::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Moto::UpdateRotate(Math::Vector3& srcMoveVec)
{

	// 何も入力が無い場合は処理しない
	if (srcMoveVec.Length() == 0.f) { return; }

	// キャラの正面方向のベクトル
	Math::Vector3 _nowDir = GetMatrix().Backward();
	_nowDir.Normalize();

	// キャラの移動方向のベクトル
	Math::Vector3 _targetDir = srcMoveVec;
	_targetDir.Normalize();

	float _nowAng = atan2(_nowDir.x, _nowDir.z);
	_nowAng = DirectX::XMConvertToDegrees(_nowAng);

	float _targetAng = atan2(_targetDir.x, _targetDir.z);
	_targetAng = DirectX::XMConvertToDegrees(_targetAng);

	// 角度の差分を求める
	float _betweenAng = _targetAng - _nowAng;
	if (_betweenAng > 180)
	{
		_betweenAng -= 360;
	}

	float _rotateAng = std::clamp(_betweenAng, -8.f, 8.f);
	m_worldRot.y += _rotateAng;
}

void Moto::OnHit()
{
	m_isExpired = true;
}
