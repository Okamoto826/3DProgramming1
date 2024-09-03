#pragma once

class GameFloor :public KdGameObject
{
public:

	GameFloor() {}
	~GameFloor()override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	//ターゲット
	void SetTarget(std::shared_ptr<KdGameObject> a_obj) { m_wpTarget = a_obj; }

private:
	//ポリゴン
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	//座標
	Math::Vector3 m_pos = {};

	//初期座標
	const float m_initialPosY = -5.f;

	//2枚目のポリゴン
	Math::Matrix m_secondMat;
	Math::Vector3 m_secPos = {};

	//フレーム数
	int m_frame = 0;

	bool m_makeItem = false;

	//ターゲット
	std::weak_ptr<KdGameObject> m_wpTarget;
};