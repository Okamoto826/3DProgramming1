#include "ResultScene.h"
#include "../SceneManager.h"

#include "../../GameObject/Result/ResultManager.h"
#include "Application/Scene/GameScene/EventManager.h"

void ResultScene::Event()
{
	if (!m_b_createResult)
	{
		// リザルト
		std::shared_ptr<ResultManager>resultManager = std::make_shared<ResultManager>();
		resultManager->SetData(EventManager::Instance().GetScore(), EventManager::Instance().GetMaxCombo());
		resultManager->Init();
		SceneManager::Instance().AddObject(resultManager);

		m_b_createResult = true;
	}
}

void ResultScene::Init()
{
	int Max = (int)pow(TEN_NUM, BaseNumberDigit) + BACK;
	if (m_score > Max) { m_score = Max; }
	if (m_combo > Max) { m_combo = Max; }
}

