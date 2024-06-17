#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Chara/CharaManager.h"

void GameScene::Event()
{
	// カメラの座標行列を作成
	Math::Matrix transmat = Math::Matrix::CreateTranslation
	(0.f, 0.f, -5.0f);

	// 行列を合成
	Math::Matrix mat =transmat;

	// カメラに行列をセット
	// この時点では画面には反映されない
	m_camera->SetCameraMatrix(mat);
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	
}

void GameScene::Init()
{
	// カメラ　生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();	// 1 メモリ確保

	std::shared_ptr<CharaManager> charaManager;
	charaManager = std::make_shared<CharaManager>();
	m_objList.push_back(charaManager);
	
}
