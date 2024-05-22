#pragma once

class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player() {}

	void Init()override;
	void DrawLit()override;

	void Update()override;

private:

	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;
};