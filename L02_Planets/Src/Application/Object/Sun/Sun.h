#pragma once

class Sun:public KdGameObject
{
public:
	Sun() { Init(); }
	~Sun()override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	float m_rotNum;
	Math::Matrix m_world;
	Math::Matrix m_rotMat;
	KdModelData m_model;
};