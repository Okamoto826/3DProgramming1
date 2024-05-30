#pragma once

class Earth :public KdGameObject
{
public:
	Earth() { Init(); }
	~Earth()override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	Math::Matrix GetMat() { return m_mWorld; };

private:

	float m_rotNum;
	float m_revoNum;
	Math::Matrix m_world;
	Math::Matrix m_revoMat;
	Math::Matrix m_rotMat;
	Math::Matrix m_transMat;
	KdModelData m_model;
};