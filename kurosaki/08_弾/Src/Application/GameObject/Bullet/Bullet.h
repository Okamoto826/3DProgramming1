#pragma once

class Tank;

class Bullet :public KdGameObject
{
public:
	Bullet() { Init(); }
	~Bullet() {}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawBright()override;
	void PostUpdate()override;
	void SetParam(Math::Vector3 _pos, Math::Vector3 _dir, float _speed, int _lifeSpan);
	void OnHit()override;

private:
	std::shared_ptr<KdModelData> m_model = nullptr;
	Math::Vector3 m_pos;
	Math::Vector3 m_dir;
	float m_speed = 0;
	float m_lifeSpan = 0;
	
};