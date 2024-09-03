#pragma once

class GameBack :public KdGameObject
{
public:

	GameBack(){}
	~GameBack()override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;

	void SetTarget(std::shared_ptr<KdGameObject> a_spTarget) { m_wpTarget = a_spTarget; }

private:
	//ポリゴン
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	//ポリゴン(最背景)
	std::shared_ptr<KdSquarePolygon> m_spBackPoly = nullptr;

	//座標
	Math::Vector3 m_pos = {};

	//座標2
	Math::Vector3 m_secPos = {};
	Math::Matrix m_secMat;

	//追従用変数
	std::weak_ptr<KdGameObject> m_wpTarget;

	//初期座標
	const Math::Vector3 m_localPos = {0.f,0.f,45.f};

	//フレーム数
	int m_frame = 0;
};