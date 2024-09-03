#pragma once

class WeaponBase;

class Player : public KdGameObject
{
public:

	Player() {}
	~Player() override{}

	void Init() override;
	void Update() override;
	void PostUpdate() override;

	void SetWeapon(const std::shared_ptr<WeaponBase>& weapon)
	{
		m_wpWeapon = weapon;
	}

	const Math::Matrix GetRotationMatrix() const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_degAng.y),
			DirectX::XMConvertToRadians(m_degAng.x),
			DirectX::XMConvertToRadians(m_degAng.z));
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(
			DirectX::XMConvertToRadians(m_degAng.y));
	}

private:

	// カメラ回転用マウス座標の原点
	POINT						m_fixMousePos{};
	// カメラ回転制御
	void UpdateRotateByMouse();

	// 武器情報
	std::weak_ptr<WeaponBase> m_wpWeapon;

	// ワールド座標
	Math::Vector3 m_pos;

	// ☆回転角度
	Math::Vector3 m_degAng;

	// 進行方向（ベクトルの向き）
	Math::Vector3 m_moveDir;

	// 移動速度（ベクトルの大きさ）
	float m_moveSpeed;

	// プレイヤー座標補正
	float m_adjustHeight;

	// 重力
	float m_gravityPow;
	float m_gravity;
	float m_jumpPow;
	bool m_jumpKeyFlg = false;
	bool m_leftKeyFlg = false;
	bool m_rightKeyFlg = false;
};