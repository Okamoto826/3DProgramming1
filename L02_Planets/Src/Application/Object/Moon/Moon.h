#pragma once

class Moon :public KdGameObject
{
public:
	Moon() { Init(); }
	~Moon()override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	float m_rotNum;
	float m_revoNum;
	float m_revoMoonNum;
	Math::Matrix m_world;
	Math::Matrix m_revoMat;
	Math::Matrix m_rotMat;
	Math::Matrix m_transMat;
	KdModelData m_model;
};