#pragma once
#include "../ResultBase.h"

class ResultScore : public ResultBase
{
public:
	ResultScore() {}
	~ResultScore() {}

	void Init()override;
	void Update()override;

	void SetScore(const int score) { m_score = score; }

private:
	int m_score{};

	const std::string ScorePng = "Asset/Textures/Result/score.png";

};




