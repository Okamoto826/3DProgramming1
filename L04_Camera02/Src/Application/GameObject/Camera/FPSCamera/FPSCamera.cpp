#include "FPSCamera.h"

void FPSCamera::Init()
{
	// 基準点(ターゲット)からどれだけ離れているか
	m_LocalPos = Math::Matrix::CreateTranslation(0, 1.5f, 0.f);

	// マウスカーソルを画面中央に固定
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void FPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = _spTarget->GetMatrix();
	}

	// カメラの回転
	UpdateRotateMouse();
	m_Rotation = GetRotationMatrix();
	m_mWorld = m_Rotation * m_LocalPos * _targetMat;

	CameraBase::Update();
}

void FPSCamera::UpdateRotateMouse()
{
	// マウスでカメラを回転させる処理
	POINT nowPos;
	GetCursorPos(&nowPos);

	POINT mouseMove{};
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 実際にカメラを回転させる処理
	m_DegAng.x += mouseMove.y * 0.15f;
	m_DegAng.y += mouseMove.x * 0.15f;

	// 回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -FLT_MAX, FLT_MAX);
}
