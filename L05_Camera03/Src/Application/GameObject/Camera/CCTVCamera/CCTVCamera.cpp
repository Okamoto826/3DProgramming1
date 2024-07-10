#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 3.0f, -10.0f);
	// 一旦行列を確定させる
	m_mWorld = m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
		//m_DegAng.x =  m_mLocalPos.Translation().z- _spTarget->GetPos().z;
		//m_DegAng.y = _spTarget->GetPos().x- m_mLocalPos.Translation().x ;
		//m_mRotation = GetRotationMatrix();
	}

	// カメラの回転
	//m_mWorld =m_mRotation*m_mLocalPos;
	UpdateLookAtRotate(_targetMat.Translation());

}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& targetPos)
{
	Math::Matrix shadowVP = DirectX::XMMatrixLookAtLH(GetPos(),targetPos,Math::Vector3::Up);

	m_mWorld = shadowVP.Invert();
}
