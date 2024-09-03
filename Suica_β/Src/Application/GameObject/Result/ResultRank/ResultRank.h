#pragma once
#include "../ResultBase.h"

class ResultRank : public ResultBase
{
public:
	ResultRank() {}
	~ResultRank() {}

	void Init()override;
	void Update()override;

	void SetData(const int score, const int combo) { m_score = score; m_combo = combo; }

private:
	enum RankType
	{
		RankType_SS,
		RankType_S,
		RankType_A,
		RankType_B,
		RankType_C,
		RankType_D,
		RankType_E,
		RankType_F,
		RankNum
	};
	enum RankScore
	{
		RankScore_SS= 15000,
		RankScore_S = 12000,
		RankScore_A = 10000,
		RankScore_B = 7000,
		RankScore_C = 5000,
		RankScore_D = 3000,
		RankScore_E = 1500,
		RankScore_F = 0
	};
	
	const Math::Color RankColor_SS  = { 0.4f,1.0f,0.4f,1.0f };
	const Math::Color RankColor_S	= { 1.0f,1.0f,0.0f,1.0f };
	const Math::Color RankColor_A	= { 1.0f,0.0f,0.0f,1.0f };
	const Math::Color RankColor_B	= { 0.0f,0.0f,1.0f,1.0f };
	const Math::Color RankColor_C	= { 1.0f,0.5f,0.0f,1.0f };
	const Math::Color RankColor_D	= { 1.0f,0.0f,1.0f,1.0f };
	const Math::Color RankColor_E	= { 1.0f,1.0f,1.0f,1.0f };
	const Math::Color RankColor_F	= { 0.5f,0.5f,0.5f,1.0f };

	int m_score{};
	int m_combo{};
	int m_rank{};
	const int ComboScoreTimes = 20;

	const std::string RankPng = "Asset/Textures/Result/rank.png";
	const int RankTexSize = 100;

	const float RankAlphaTrans = 0.02f;

};



