#pragma once
class Tank;

class Yama :public KdGameObject
{
public:
	Yama() { Init(); }
	~Yama() {}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void UpdateRotate(Math::Vector3& srcMoveVec);

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; };
	void SetTarget(std::weak_ptr<Tank> _target)
	{
		if (_target.expired() == false)
		{
			m_target = _target;
		}
	};

	void OnHit()override;

private:
	std::shared_ptr<KdModelData> m_model = nullptr;
	std::weak_ptr<Tank> m_target;
	Math::Vector3 m_pos;
	Math::Vector3 m_worldRot = {};
	// 重力
	float m_gravityPow;
	float m_gravity;
	float m_jumpPow;

	float m_speed = 0.05;
};