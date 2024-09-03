#include "ResultManager.h"

#include "ResultScore/ResultScore.h"
#include "ResultCombo/ResultCombo.h"
#include "ResultRank/ResultRank.h"
#include "resultback/ResultBack.h"

#include "../../Scene/SceneManager.h"

void ResultManager::Init()
{
	m_resultStoryCnt = ResetCount;
}

void ResultManager::Update()
{
	m_resultStoryCnt++;
	
	switch (m_resultStoryCnt)
	{
	case ScoreTime:	CreateScore();	break;
	case ComboTime:	CreateCombo();	break;
	case RankTime:	CreateRank();	break;
	case BackTime:	CreateBack();	break;
	default:break;
	}
}

void ResultManager::CreateScore()const
{
	// スコア
	std::shared_ptr<ResultScore>resultScore = std::make_shared<ResultScore>();
	resultScore->SetScore(m_score);
	resultScore->SetPos(ScoreBasePosX, ScoreBasePosY);
	resultScore->Init();
	SceneManager::Instance().AddObject(resultScore);
}
void ResultManager::CreateCombo()const
{
	// コンボ
	std::shared_ptr<ResultCombo>resultCombo = std::make_shared<ResultCombo>();
	resultCombo->SetCombo(m_combo);
	resultCombo->SetPos(ComboBasePosX, ComboBasePosY);
	resultCombo->Init();
	SceneManager::Instance().AddObject(resultCombo);
}
void ResultManager::CreateRank()const
{
	// ランク
	std::shared_ptr<ResultRank>resultRank = std::make_shared<ResultRank>();
	resultRank->SetData(m_score,m_combo);
	resultRank->SetPos(RankBasePosX, RankBasePosY);
	resultRank->SetScale(RankBaseScale);
	resultRank->Init();
	SceneManager::Instance().AddObject(resultRank);
}
void ResultManager::CreateBack()const
{
	// バック
	std::shared_ptr<ResultBack>resultBack = std::make_shared<ResultBack>();
	resultBack->SetPos(BackBasePosX, BackBasePosY);
	resultBack->Init();
	SceneManager::Instance().AddObject(resultBack);
}
