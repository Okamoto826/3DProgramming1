#pragma once
class BackTree :public KdGameObject
{
public:
	BackTree() { Init(); }
	~BackTree() {}

	void Init()override;
	void DrawUnLit()override;

private:

	KdSquarePolygon m_polygon;
};