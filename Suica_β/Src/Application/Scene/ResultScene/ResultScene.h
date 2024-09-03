#pragma once

#include"../BaseScene/BaseScene.h"



class ResultScene : public BaseScene
{
public:

	ResultScene() {}
	~ResultScene() {}

	void SetData(const int score,const int combo)
	{
		m_score = score;
		m_combo = combo;
	}
	void Init() override;

private:

	void Event() override;

	int m_score{};	// スコア
	int m_combo{};	// コンボ

	bool m_b_createResult = false;
	const int BaseNumberDigit = 5;

};
