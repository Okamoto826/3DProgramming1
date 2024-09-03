#include "GameScene.h"
#include"../SceneManager.h"

//オブジェクト
#include "Application/GameObject/Game/Back/GameBack.h"
#include "Application/GameObject/Game/Floor/GameFloor.h"
#include "Application/GameObject/Game/Player/Player.h"
#include "Application/GameObject/Game/WaterMellon/WaterMellon.h"
#include "Application/GameObject/UI/Score/Score.h"
#include "Application/GameObject/UI/Time/Time.h"
#include "Application/GameObject/Club/Club.h"
#include "Application/GameObject/UI/Time/Time.h"

//カメラ
#include "Application/GameObject/Camera/FPSCamera/FPSCamera.h"

void GameScene::Event()
{
	if (m_time->GameEnd())
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
	}
}

void GameScene::Init()
{
	//背景
	std::shared_ptr<GameBack> back = std::make_shared<GameBack>();
	back->Init();
	m_objList.push_back(back);


	//床
	std::shared_ptr<GameFloor> floor = std::make_shared<GameFloor>();
	floor->Init();
	m_objList.push_back(floor);

	//プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	m_objList.push_back(player);

	//FPSカメラ(仮)
	std::shared_ptr<FPSCamera> fps = std::make_shared<FPSCamera>();
	fps->Init();
	m_objList.push_back(fps);

	//UI
	std::shared_ptr<Score> score = std::make_shared<Score>();
	score->Init();
	m_objList.push_back(score);

	m_time = std::make_shared<Time>();
	m_time->Init();
	m_objList.push_back(m_time);

	//棒
	std::shared_ptr<Club> club = std::make_shared<Club>();
	m_objList.push_back(club);


	fps->SetTarget(player);
	floor->SetTarget(player);
	club->SetTarget(player);
	back->SetTarget(player);

	Math::Viewport _viewPort;
	KdDirect3D::Instance().CopyViewportInfo(_viewPort);
	const int _width = _viewPort.width;
	const int _height = _viewPort.height;
	KdEffekseerManager::GetInstance().Create(_width, _height);
	KdEffekseerManager::GetInstance().SetCamera(fps->GetCamera());
}
