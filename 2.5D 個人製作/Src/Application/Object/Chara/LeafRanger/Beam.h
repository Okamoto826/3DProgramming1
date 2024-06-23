#pragma once

class Beam :public KdGameObject
{
public:

	enum NowSt
	{
		Move = 1 << 0,
		Hit = 1 << 1,
	};
	Beam() { Init(); };
	~Beam() {};
	void Init()override;
	void Update()override;
	void DrawLit()override;
	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

private:
	// 板ポリゴン
	KdSquarePolygon m_polygon;
	Math::Vector3	m_pos;
	int				m_dmg;
	int				m_timeCnt;
	NowSt			m_nowSt;

};