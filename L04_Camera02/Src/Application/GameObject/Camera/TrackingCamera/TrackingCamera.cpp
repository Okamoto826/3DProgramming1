#include "TrackingCamera.h"

void TrackingCamera::Init()
{
	// 基準点(ターゲット)からどれだけ離れているか
	m_LocalPos = Math::Matrix::CreateTranslation(0, 6.0f, -5.0f);

	// どれだけ傾けているか
	m_Rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	CameraBase::Init();
}

void TrackingCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = _spTarget->GetMatrix();
	}

	m_mWorld = m_Rotation * m_LocalPos * _targetMat;

	CameraBase::Update();
}
