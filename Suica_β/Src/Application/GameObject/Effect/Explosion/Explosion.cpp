#include "Explosion.h"

void Explosion::Update()
{
	m_anime += m_cntSed;

	if (m_anime > 18)
	{
		m_isExpired = true;
	}
	m_spPoly->SetUVRect((int)m_anime);
}

void Explosion::Init()
{
	EffectBase::Init();

	m_spPoly->SetMaterial("Asset/Textures/Effect/bakuhatu.png");
	m_spPoly->SetSplit(18, 1);
	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_size = { 10,10,1 };
	m_cntSed = 0.5f;
}
