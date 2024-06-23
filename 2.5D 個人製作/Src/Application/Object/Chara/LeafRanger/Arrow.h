#pragma once

class Arrow:public KdGameObject
{
public:

	enum NowSt
	{
		Move = 1 << 0,
		Hit = 1 << 1,
	};
	Arrow() { Init(); };
	 ~Arrow() {};
	 void Init()override;
	 void Update()override;
	 void PostUpdate()override;
	 void DrawLit()override;
	 void OnHit()override;
	 void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

private:
	// 板ポリゴン
	KdSquarePolygon m_polygon;
	Math::Vector3	m_pos;
	int				m_dmg;
	int				m_timeCnt;
	int				m_lifeTime = 120;
	Math::Vector3	m_speed;
	NowSt			m_nowSt;
	float			m_gravity;

};