#pragma once

class WeaponBase :public KdGameObject
{
public:
	WeaponBase() {}
	virtual ~WeaponBase() override{}

	virtual void Update() override;

	virtual void DrawLit() override;

	virtual void ShotBullet(const bool rayFlg = false) = 0;

	void SetParent(const std::shared_ptr<KdGameObject>& parent)
	{
		m_wpParent = parent;
	}

protected:

	// モデル情報
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	// 親(持ち主)の情報
	std::weak_ptr<KdGameObject> m_wpParent;

	// 親から武器本体へローカル行列(相対位置)
	Math::Matrix m_localMat;

	// 親から銃口へのローカル行列(相対位置)
	Math::Matrix m_localMuzzleMat;

	// 弾発射フラグ
	bool m_shotFlg = false;

	// レイ弾発射フラグ
	bool m_rayBulletFlg = false;
};