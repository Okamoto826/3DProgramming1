#pragma once

class Enemy :public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() {}

	void Init()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; };

	void Update()override;
	void PostUpdate() override;

private:

	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;
	float m_goal = 0;
	int m_dir;
	float m_speed = 0.02;
	float m_nowSpl;
	float m_gravity;
};