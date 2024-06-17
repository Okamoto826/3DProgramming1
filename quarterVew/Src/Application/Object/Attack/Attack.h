#pragma once

class Attack :public KdGameObject
{
public:

	Attack() {};
	~Attack() override {};

	void Update() override;

	void DrawUnLit() override;

	void Init() override;

private:

	// 板ポリゴン
	KdSquarePolygon m_polygon;

	// アニメーション情報
	float m_animaCnt;
	float m_animeSpeed;

	// 攻撃判定エリア
	float m_attackArea;
};