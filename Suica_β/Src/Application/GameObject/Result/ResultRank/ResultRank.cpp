#include "ResultRank.h"

void ResultRank::Init()
{
	m_sp_tex->Load(RankPng);

	ResultBase::Init();

	// スコアとランク
	m_score += m_combo * ComboScoreTimes;

	if		(m_score >= RankScore_SS) { m_rank = RankType_SS; m_color = RankColor_SS;}
	else if (m_score >= RankScore_S ) { m_rank = RankType_S;  m_color = RankColor_S; }
	else if (m_score >= RankScore_A ) { m_rank = RankType_A;  m_color = RankColor_A; }
	else if (m_score >= RankScore_B ) { m_rank = RankType_B;  m_color = RankColor_B; }
	else if (m_score >= RankScore_C ) { m_rank = RankType_C;  m_color = RankColor_C; }
	else if (m_score >= RankScore_D ) { m_rank = RankType_D;  m_color = RankColor_D; }
	else if (m_score >= RankScore_E ) { m_rank = RankType_E;  m_color = RankColor_E; }
	else if (m_score >= RankScore_F ) { m_rank = RankType_F;  m_color = RankColor_F; }

	m_rect = { m_rank * RankTexSize, ZERO, RankTexSize, RankTexSize };
	m_color.A(MinColor);
	m_scale.x /= RankNum;
}

void ResultRank::Update()
{
	float alpha = m_color.A();
	if (alpha < MaxColor) { m_color.A(alpha + RankAlphaTrans); }
}
