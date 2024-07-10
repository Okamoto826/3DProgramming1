#include "Yama.h"
#include"../Tank/Tank.h"
#include"../../Scene/SceneManager.h"

void Yama::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/yama/yama.gltf");
	// 重力
	m_gravityPow = 0.01f;
	m_gravity = 0.0f;

	m_jumpPow = -0.3;


	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Yama", m_model, KdCollider::TypeDamage);
}

void Yama::Update()
{
	Math::Vector3 m_move = {};
	m_speed = 0.05;
	if (m_target.expired() == false)
	{

		Math::Vector3 targetPos = m_target.lock()->GetPos();
		m_move = targetPos - m_pos;
		if (m_move.Length() < m_speed)m_speed = m_move.Length();
	}
	m_move.Normalize();
	m_pos += m_move * m_speed;
	UpdateRotate(m_move);

	// 重力をキャラに反映
	m_pos.y -= m_gravity;
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
		m_gravity = m_jumpPow;
	}
	m_gravity += m_gravityPow;

	// キャラクターのワールド行列を創る処理
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotMat * transMat;
}



void Yama::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Yama::UpdateRotate(Math::Vector3& srcMoveVec)
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
