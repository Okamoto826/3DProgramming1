#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Stage/Stage.h"
#include"../../Object/Chara/CharaManager.h"
#include"../../Object/Back/Back.h"

void GameScene::Event()
{
	// カメラの座標行列を作成
	Math::Vector3 cameraPos = { 0.f,0.f,-5.0f };
	Math::Matrix transmat = Math::Matrix::CreateTranslation(cameraPos);

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

	//②フォグ（霧）												距離　　高さ
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, false);
	//																		色		濃さ
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1.0,1.0,1.0 }, 0.01);


	std::shared_ptr<Stage> stage;
	stage = std::make_shared<Stage>();
	m_objList.push_back(stage);

	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	m_objList.push_back(back);

	std::shared_ptr<CharaManager> charaManager;
	charaManager = std::make_shared<CharaManager>();
	m_objList.push_back(charaManager);
	
}
