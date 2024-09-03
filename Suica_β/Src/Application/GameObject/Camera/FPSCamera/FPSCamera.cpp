#include "FPSCamera.h"

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 7.5f, 0.0f);
	m_spCamera->SetFocus(10, 3, 20);

}

void FPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat	= Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget	= m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));


	// カメラの回転
	m_mWorld	= m_mRotation * m_mLocalPos * _targetMat;

	CameraBase::Update();
}
