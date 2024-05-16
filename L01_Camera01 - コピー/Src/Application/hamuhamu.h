#pragma once

class HamuHamu :public KdGameObject
{
public:
	HamuHamu();
	~HamuHamu()	override;

public:
	void Init()	override;
	void Update()	override;
	void DrawLit()	override;

private:
	//ポリゴン
	std::shared_ptr<KdSquarePolygon>	m_spPoly = nullptr;

	
};
