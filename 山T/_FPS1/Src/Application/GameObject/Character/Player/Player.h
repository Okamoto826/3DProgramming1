﻿#pragma once

class CameraBase;

class Player : public KdGameObject
{
public:
	Player() {}
	virtual ~Player()	override {}

	void Init()				override;
	void Update()			override;
	
	void UpdateRotateByMouse();

	void SetCamera(std::shared_ptr<CameraBase> _camera) 
	{
		m_wpCamera = _camera; 
	};

private:

	// カメラ情報
	std::weak_ptr<CameraBase>			m_wpCamera;

	// ワールド座標
	Math::Vector3 m_pos = Math::Vector3::Zero;

	// 進行方向(ベクトルの向き)
	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	// 移動速度(ベクトルの大きさ)
	const float m_moveSpeed = 0.3f;

	// カメラ回転用マウス座標の差分
	POINT						m_FixMousePos{};

	Math::Vector3				m_DegAng = Math::Vector3::Zero;
};