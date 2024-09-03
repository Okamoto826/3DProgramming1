#pragma once

class EffectBase :public KdGameObject
{
public:

	EffectBase() {}
	virtual ~EffectBase()override {}

	virtual void Update()override {}
	virtual void PostUpdate()override;
	virtual void Init()override;
	virtual void DrawUnLit()override;
	virtual void DrawBright()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetTarget(const std::shared_ptr<KdGameObject>& target){ m_wpTarget = target; }


protected:

	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	std::weak_ptr<KdGameObject> m_wpTarget;

	Math::Vector3 m_pos = Math::Vector3::Zero;

	Math::Vector3 m_size = Math::Vector3::One;

	Math::Color m_color = kWhiteColor;

	float m_cntSed = 0;				// アニメのスピード
	float m_anime = 0;				// アニメーションカウント
};