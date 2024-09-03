﻿#include "FPSCamera.h"

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)の目線
	//m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, 0.0f);

	//SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void FPSCamera::PostUpdate()
{
	//// ターゲットの行列(有効な場合利用する)
	//Math::Matrix								_targetMat	= Math::Matrix::Identity;
	//const std::shared_ptr<const KdGameObject>	_spTarget	= m_wpTarget.lock();	
	//if (_spTarget)
	////{
	//	_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	//}

	//// カメラの回転
	//m_mRotation = GetRotationMatrix();
	////			　自身の回転角度×目線へのローカル行列×プレイヤーの座標
	//m_mWorld	= m_mRotation * m_mLocalPos * _targetMat;

	Math::Matrix								_targetMat	= Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = _spTarget->GetMatrix();
	}

	m_mWorld = _targetMat;

	CameraBase::PostUpdate();
}