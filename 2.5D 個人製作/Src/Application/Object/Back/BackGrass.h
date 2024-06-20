#pragma once

class BackGrass :public KdGameObject
{
public:
	BackGrass() { Init(); }
	~BackGrass() {}

	void Init()override;
	void DrawUnLit()override;

private:

	KdSquarePolygon m_polygon;
};