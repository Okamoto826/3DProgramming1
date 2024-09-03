#pragma once

class ResultManager : public KdGameObject
{
public:
	ResultManager() {}
	~ResultManager() {}

	void Init()override;
	void Update()override;

	void SetData(const int score, const int combo)
	{
		m_score = score;
		m_combo = combo; 
	};

private:
	void CreateScore()const;
	void CreateCombo()const;
	void CreateRank()const;
	void CreateBack()const;

	//====================
	// リザルトデータ
	//====================
	int m_score{};
	int m_combo{};
	
	// スコア
	const int ScoreBasePosX = -250;
	const int ScoreBasePosY = 250;
			 
	// コンボ
	const int ComboBasePosX = ScoreBasePosX;
	const int ComboBasePosY = ScoreBasePosY - 100;
			 
	// ランク
	const int RankBasePosX  = 0;
	const int RankBasePosY  = -50;
	const Math::Vector2 RankBaseScale = { 2.f,2.f };

	// バック
	const int BackBasePosX  = 0;
	const int BackBasePosY  = RankBasePosY - 200;

	//====================
	// リザルトストーリー
	//====================

	int m_resultStoryCnt{};
	
	enum StoryPoint
	{
		ScoreTime = 5,
		ComboTime = 65,
		RankTime = 155,
		BackTime = 225
	};


};
