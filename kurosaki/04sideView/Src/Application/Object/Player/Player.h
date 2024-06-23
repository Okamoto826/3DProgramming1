#pragma once


class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player() {}

	void Init()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void Update()override;

	void PostUpdate() override;

private:

	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;
	float m_nowSpl;
	float m_gravity;
};