#pragma once

class Tank;

class Moto :public KdGameObject
{
public:
	Moto() { Init(); }
	~Moto() {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; };
	void SetTarget(std::weak_ptr<Tank> _target)
	{
		if (_target.expired() == false)
		{
			m_target = _target;
		}
	};

private:
	std::shared_ptr<KdModelData> m_model = nullptr;
	std::weak_ptr<Tank> m_target;
	
	Math::Vector3 m_pos;
	float m_speed = 0.06;
};