#pragma once

class CharaManager:public KdGameObject
{
public:
	CharaManager() { Init(); };
	~CharaManager() {};
	void Init()override;
	void Update()override;
	void DrawSprite() override;
private:
	bool keyFlg = false;
	int m_count = 0;
	int m_cost = 5;
	KdTexture m_gageTex;
	KdTexture m_barTex;
	KdTexture m_numTex;
	KdTexture m_paceeTex;
	KdTexture m_rangerTex;
	KdTexture m_maulerTex;
	KdTexture m_monkTex;
};
